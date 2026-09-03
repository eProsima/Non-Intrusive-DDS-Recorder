#!/usr/bin/env python3
"""Check the default database schema of the Non-Intrusive DDS Recorder.

The recorder has no C++ test suite, so this script is the regression check for the
DDS Record & Replay schema, which is what the recorder writes by default.  It records the
fixture captures twice, once with no argument and once with -queryable, and asserts the shape
and the content of both databases.

The expected numbers were obtained by decoding the captures independently of the recorder:
HelloWorld.pcap carries 31 user DATA submessages of which 30 have a distinct
(writer_guid, sequence_number), and complextype_in_sequence.pcap carries 13 with no
duplicates.

The recorder returns the same non-zero exit status on success and on failure, so the exit
status is never consulted; stdout and the resulting database are.

Standard library only.  The dev container has no sqlite3 CLI.
"""

import argparse
import os
import re
import shutil
import sqlite3
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CAPTURES = os.path.join(REPO, 'utils', 'pcTests', 'capturefiles')
HELLOWORLD = os.path.join(REPO, 'examples', 'HelloWorld', 'HelloWorld.pcap')

MONITOR_TABLES = {
    'Types', 'Topics', 'Messages',
    'Partitions', 'TopicsPartitions', 'MessagesPartitions',
}
LEGACY_TABLES = {'_topics', '_endpoints', '_endpointDiscoveryMessages'}

GUID_RE = re.compile(r'^([0-9a-f]{2}\.){11}[0-9a-f]{2}\|[0-9a-f]{1,2}(\.[0-9a-f]{1,2}){3}$')
TIME_RE = re.compile(r'^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{9}$')

# Encapsulation identifiers a CDR payload may legitimately start with.
VALID_ENCAPSULATIONS = {0x0000, 0x0001, 0x0002, 0x0003,
                        0x0006, 0x0007, 0x0008, 0x0009,
                        0x000a, 0x000b, 0x000c, 0x000d}


class Failure(Exception):
    pass


class Checker:
    def __init__(self):
        self.checks = 0
        self.failures = []

    def check(self, label, condition, detail=''):
        self.checks += 1
        if condition:
            print('  ok   %s' % label)
        else:
            print('  FAIL %s%s' % (label, (' -- ' + detail) if detail else ''))
            self.failures.append(label)

    def equal(self, label, actual, expected):
        self.check(label, actual == expected, 'got %r, expected %r' % (actual, expected))


def run_recorder(recorder, db_path, capture, queryable=False, idl=None):
    """Record a capture and return the recorder's combined output.

    The DDS Record & Replay schema is the default, so it needs no argument; -queryable selects
    the per-topic-table schema instead.
    """
    command = [recorder, '-db', db_path]
    if queryable:
        command.append('-queryable')
    if idl:
        command += ['-idl', idl]
    command.append(capture)
    completed = subprocess.run(command, capture_output=True, text=True)
    return completed.stdout + completed.stderr


def packets(output):
    match = re.search(r'Number of processed RTPS packets:\s*(\d+)', output)
    return int(match.group(1)) if match else None


def tables(db_path):
    connection = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    try:
        return {row[0] for row in connection.execute(
            "SELECT name FROM sqlite_master WHERE type = 'table'")}
    finally:
        connection.close()


def query(db_path, sql, parameters=()):
    connection = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    try:
        return list(connection.execute(sql, parameters))
    finally:
        connection.close()


def check_helloworld(checker, recorder, workdir):
    print('\n== HelloWorld.pcap, default schema ==')
    db = os.path.join(workdir, 'hw_monitor.db')
    output = run_recorder(recorder, db, HELLOWORLD)

    if not os.path.exists(db):
        raise Failure('the recorder produced no database:\n' + output)

    checker.equal('processed 147 RTPS packets', packets(output), 147)

    found = tables(db)
    checker.equal('exactly the 6 Record & Replay tables', found, MONITOR_TABLES)
    checker.check('no legacy tables', not (found & LEGACY_TABLES),
                  'found %s' % sorted(found & LEGACY_TABLES))

    if not (MONITOR_TABLES <= found):
        raise Failure('the Record & Replay schema is missing, cannot check content')

    rows = query(db, 'SELECT writer_guid, sequence_number, data_json, data_cdr, '
                     'data_cdr_size, topic, type, key, log_time, publish_time '
                     'FROM Messages ORDER BY sequence_number')
    checker.equal('Messages has 30 rows (31 transmissions, 1 duplicate seq)', len(rows), 30)

    bad_size = [r[1] for r in rows if r[4] != len(r[3] or b'') or r[4] <= 0]
    checker.check('data_cdr_size == length(data_cdr) and > 0 everywhere',
                  not bad_size, 'sequence numbers %s' % bad_size[:5])

    bad_encap = [r[1] for r in rows
                 if len(r[3] or b'') < 4
                 or int.from_bytes(r[3][:2], 'big') not in VALID_ENCAPSULATIONS]
    checker.check('data_cdr starts with a valid encapsulation id',
                  not bad_encap, 'sequence numbers %s' % bad_encap[:5])

    checker.check('data_json is empty everywhere',
                  all(r[2] == '' for r in rows),
                  'distinct values %s' % sorted({r[2] for r in rows})[:3])
    checker.check("key is '{}' everywhere", all(r[7] == '{}' for r in rows),
                  'distinct values %s' % sorted({r[7] for r in rows})[:3])

    checker.equal('writer_guid is the expected GUID',
                  sorted({r[0] for r in rows}),
                  ['c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3'])
    checker.check('writer_guid matches the Fast DDS text format',
                  all(GUID_RE.match(r[0]) for r in rows))

    checker.check('log_time / publish_time are fixed-width with 9 decimals',
                  all(TIME_RE.match(r[8]) and TIME_RE.match(r[9]) for r in rows),
                  'e.g. %r / %r' % (rows[0][8], rows[0][9]) if rows else '')

    checker.equal('sequence numbers are 1..30',
                  sorted(r[1] for r in rows), list(range(1, 31)))
    checker.equal('topic / type on every row',
                  sorted({(r[5], r[6]) for r in rows}),
                  [('Example HelloWorld', 'HelloWorld')])

    topics = query(db, 'SELECT name, type, qos, is_ros2_topic FROM Topics')
    checker.equal('one Topics row', len(topics), 1)
    if topics:
        checker.equal('Topics identifies the topic',
                      topics[0][:2], ('Example HelloWorld', 'HelloWorld'))
        checker.equal('is_ros2_topic', topics[0][3], 'false')

    types = query(db, 'SELECT name, information, object, is_ros2_type, idl FROM Types')
    checker.equal('one Types row', len(types), 1)
    if types:
        checker.equal('Types name', types[0][0], 'HelloWorld')
        checker.check('Types.idl holds the IDL rendered from the wire TypeCode',
                      'struct HelloWorld' in (types[0][4] or ''),
                      'got %r' % (types[0][4],))
        checker.equal('Types.information is empty', types[0][1], '')
        checker.equal('Types.object is empty', types[0][2], '')

    checker.equal('Partitions holds the single empty partition',
                  query(db, 'SELECT name FROM Partitions'), [('',)])
    checker.equal('TopicsPartitions has 1 row',
                  query(db, 'SELECT COUNT(*) FROM TopicsPartitions')[0][0], 1)
    checker.equal('MessagesPartitions has 30 rows',
                  query(db, 'SELECT COUNT(*) FROM MessagesPartitions')[0][0], 30)

    # publish_time must be derived from the RTPS fraction, not from the raw fraction word.
    print('\n== HelloWorld.pcap, -queryable schema (regression guard) ==')
    legacy = os.path.join(workdir, 'hw_legacy.db')
    legacy_output = run_recorder(recorder, legacy, HELLOWORLD, queryable=True)
    checker.equal('processed 147 RTPS packets', packets(legacy_output), 147)
    legacy_tables = tables(legacy)
    checker.check('legacy discovery tables present',
                  LEGACY_TABLES <= legacy_tables,
                  'found %s' % sorted(legacy_tables))
    checker.check('per-topic table present', 'Example_HelloWorld' in legacy_tables)
    checker.check('no Record & Replay tables', not (legacy_tables & MONITOR_TABLES),
                  'found %s' % sorted(legacy_tables & MONITOR_TABLES))
    if 'Example_HelloWorld' in legacy_tables:
        checker.equal('legacy table still has 31 rows',
                      query(legacy, 'SELECT COUNT(*) FROM Example_HelloWorld')[0][0], 31)

        legacy_prefixes = {second_to_prefix(r[0]) for r in query(
            legacy, 'SELECT src_timestamp_sec FROM Example_HelloWorld')}
        skewed = [r[1] for r in rows if r[9][:19] not in legacy_prefixes]
        checker.check('publish_time second matches the source timestamp '
                      '(catches a missed fraction->nanos conversion)',
                      not skewed, 'sequence numbers %s' % skewed[:5])


def second_to_prefix(epoch_seconds):
    import datetime
    moment = datetime.datetime.fromtimestamp(epoch_seconds, datetime.timezone.utc)
    return moment.strftime('%Y-%m-%d %H:%M:%S')


def check_untyped_capture(checker, recorder, workdir):
    """complextype_in_sequence has no recordable type, so the legacy schema stores nothing."""
    capture = os.path.join(CAPTURES, 'complextype_in_sequence.pcap')
    if not os.path.exists(capture):
        return

    print('\n== complextype_in_sequence.pcap: recorded despite having no usable type ==')
    db = os.path.join(workdir, 'cts_monitor.db')
    run_recorder(recorder, db, capture)
    if not os.path.exists(db) or not (MONITOR_TABLES <= tables(db)):
        checker.check('the Record & Replay schema was produced', False)
        return

    checker.equal('Messages has 13 rows',
                  query(db, 'SELECT COUNT(*) FROM Messages')[0][0], 13)
    checker.check('every row carries a CDR payload',
                  query(db, 'SELECT COUNT(*) FROM Messages '
                            'WHERE data_cdr_size > 0')[0][0] == 13)

    legacy = os.path.join(workdir, 'cts_legacy.db')
    run_recorder(recorder, legacy, capture, queryable=True)
    legacy_tables = tables(legacy)
    user_tables = legacy_tables - LEGACY_TABLES
    checker.check('the queryable schema still records no topic table for it',
                  not user_tables, 'found %s' % sorted(user_tables))


def check_idl_metadata(checker, recorder, workdir):
    """shapes.pcapng has no TypeCode on the wire; -idl must fill Types.information."""
    capture = os.path.join(REPO, 'shapes.pcapng')
    idl = os.path.join(REPO, 'Shape.idl')
    if not (os.path.exists(capture) and os.path.exists(idl)):
        print('\n== shapes.pcapng / Shape.idl absent, skipping the -idl metadata check ==')
        return

    print('\n== shapes.pcapng: -idl fills Types.information ==')
    without = os.path.join(workdir, 'shapes_noidl.db')
    run_recorder(recorder, without, capture)
    withidl = os.path.join(workdir, 'shapes_idl.db')
    run_recorder(recorder, withidl, capture, idl=idl)

    for path in (without, withidl):
        if not os.path.exists(path) or not (MONITOR_TABLES <= tables(path)):
            checker.check('the Record & Replay schema was produced for shapes.pcapng', False)
            return

    square = query(without, "SELECT name, type FROM Topics WHERE name = 'Square'")
    checker.equal('Square topic is discovered without any IDL',
                  square, [('Square', 'ShapeType')])

    info_without = query(without, "SELECT idl FROM Types WHERE name = 'ShapeType'")
    checker.equal('Types.idl is empty without -idl',
                  [r[0] for r in info_without], [''])

    info_with = query(withidl, "SELECT idl, information FROM Types WHERE name = 'ShapeType'")
    checker.equal('Types row for ShapeType exists with -idl', len(info_with), 1)
    if info_with:
        checker.check('Types.idl holds the IDL from the file',
                      'struct ShapeType' in (info_with[0][0] or ''),
                      'got %r' % (info_with[0][0],))
        checker.equal('Types.information stays empty even with -idl',
                      info_with[0][1], '')

    checker.equal('the two runs agree on the topic set',
                  query(without, 'SELECT COUNT(*) FROM Topics')[0][0],
                  query(withidl, 'SELECT COUNT(*) FROM Topics')[0][0])


def check_other_fixtures(checker, recorder, workdir):
    """Every remaining fixture must record at least one message in the default schema."""
    names = ('basic_types', 'arrays', 'sequences', 'unions', 'recursive_structs')
    print('\n== remaining fixtures record messages in the default schema ==')
    for name in names:
        capture = os.path.join(CAPTURES, name + '.pcap')
        if not os.path.exists(capture):
            continue
        db = os.path.join(workdir, name + '_monitor.db')
        run_recorder(recorder, db, capture)
        if not os.path.exists(db) or not (MONITOR_TABLES <= tables(db)):
            checker.check('%s: the Record & Replay schema was produced' % name, False)
            continue
        count = query(db, 'SELECT COUNT(*) FROM Messages')[0][0]
        consistent = query(db, 'SELECT COUNT(*) FROM Messages '
                               'WHERE data_cdr_size != length(data_cdr) '
                               'OR data_cdr_size <= 0')[0][0]
        checker.check('%s: %d message(s), all with a consistent CDR blob'
                      % (name, count), count > 0 and consistent == 0,
                      'messages=%d inconsistent=%d' % (count, consistent))


def main(argv=None):
    parser = argparse.ArgumentParser(
        description='Check the default database schema of the Non-Intrusive DDS Recorder.')
    parser.add_argument('-r', '--recorder',
                        default=os.environ.get('DDS_RECORDER', 'dds_recorder'),
                        help='path to the dds_recorder binary '
                             '(default: $DDS_RECORDER or dds_recorder on PATH)')
    parser.add_argument('-k', '--keep', action='store_true',
                        help='keep the generated databases for inspection')
    args = parser.parse_args(argv)

    recorder = args.recorder
    if os.path.sep not in recorder:
        resolved = shutil.which(recorder)
        if resolved is None:
            print('error: %s not found on PATH; pass --recorder or set DDS_RECORDER'
                  % recorder, file=sys.stderr)
            return 2
        recorder = resolved
    if not os.access(recorder, os.X_OK):
        print('error: %s is not executable' % recorder, file=sys.stderr)
        return 2

    print('recorder: %s' % recorder)

    checker = Checker()
    workdir = tempfile.mkdtemp(prefix='default_schema_')
    try:
        check_helloworld(checker, recorder, workdir)
        check_untyped_capture(checker, recorder, workdir)
        check_idl_metadata(checker, recorder, workdir)
        check_other_fixtures(checker, recorder, workdir)
    except Failure as failure:
        print('\nABORTED: %s' % failure, file=sys.stderr)
        return 1
    finally:
        if args.keep:
            print('\ndatabases kept in %s' % workdir)
        else:
            shutil.rmtree(workdir, ignore_errors=True)

    print('\n%d check(s), %d failure(s)' % (checker.checks, len(checker.failures)))
    if checker.failures:
        for label in checker.failures:
            print('  - %s' % label)
        return 1
    print('OK')
    return 0


if __name__ == '__main__':
    sys.exit(main())
