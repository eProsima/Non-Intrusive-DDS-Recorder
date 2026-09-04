#!/usr/bin/env python3
"""Check the database schema of the Non-Intrusive DDS Recorder.

The recorder has no C++ test suite, so this script is the regression check for both halves of
the schema.  The *DDS Record & Replay* tables are always written; -queryable adds to them,
rather than replacing them as it once did, so a recording made with it is still replayable.
The script records the fixture captures both ways and asserts the shape and the content.

Every data type now comes from the file given with -idl, so each capture is recorded with the
IDL file that sits beside it.  Without one the recording still happens, it just carries no type
description and gets no per-topic table.

The expected numbers were obtained by decoding the captures independently of the recorder:
HelloWorld.pcap carries 31 user DATA submessages of which 30 have a distinct
(writer_guid, sequence_number), and complextype_in_sequence.pcap carries 13 with no
duplicates.

The recorder returns the same non-zero exit status on success and on failure, so the exit
status is never consulted; stdout and the resulting database are.

Standard library only.  The dev container has no sqlite3 CLI.
"""

import argparse
import datetime
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
HELLOWORLD_IDL = os.path.join(REPO, 'examples', 'HelloWorld', 'HelloWorld.idl')

# Written whatever the arguments.
MONITOR_TABLES = {
    'Types', 'Topics', 'Messages',
    'Partitions', 'TopicsPartitions', 'MessagesPartitions',
}

# Added by -queryable, beside the per-topic data tables.
QUERYABLE_TABLES = {'Endpoints', 'DiscoveryMessages', 'MessagesCapture', 'DataTables'}

# Dropped with the TypeCode support they belonged to.
REMOVED_TABLES = {'_topics', '_endpoints', '_endpointDiscoveryMessages'}

GUID_RE = re.compile(r'^([0-9a-f]{2}\.){11}[0-9a-f]{2}\|[0-9a-f]{1,2}(\.[0-9a-f]{1,2}){3}$')
PREFIX_RE = re.compile(r'^([0-9a-f]{2}\.){11}[0-9a-f]{2}$')
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
    """Record a capture and return the recorder's combined output."""
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


def errors(output):
    return sorted({line for line in output.splitlines() if line.startswith('ERROR')})


def _objects(db_path, kind):
    connection = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    try:
        return {row[0] for row in connection.execute(
            "SELECT name FROM sqlite_master WHERE type = ? AND name NOT LIKE 'sqlite_%'",
            (kind,))}
    finally:
        connection.close()


def tables(db_path):
    return _objects(db_path, 'table')


def views(db_path):
    return _objects(db_path, 'view')


def indices(db_path):
    return _objects(db_path, 'index')


def query(db_path, sql, parameters=()):
    connection = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    try:
        return list(connection.execute(sql, parameters))
    finally:
        connection.close()


def one(db_path, sql, parameters=()):
    return query(db_path, sql, parameters)[0][0]


def capture_idl(name):
    """The IDL file that sits beside a capture, or None when it has none."""
    path = os.path.join(CAPTURES, name + '.idl')
    return path if os.path.exists(path) else None


def seconds_between(first, second):
    """Distance in seconds between two 'YYYY-MM-DD HH:MM:SS.nnnnnnnnn' stamps."""
    fmt = '%Y-%m-%d %H:%M:%S'
    a = datetime.datetime.strptime(first[:19], fmt)
    b = datetime.datetime.strptime(second[:19], fmt)
    return abs((a - b).total_seconds())


def check_helloworld_default(checker, recorder, workdir):
    print('\n== HelloWorld.pcap, default schema ==')
    db = os.path.join(workdir, 'hw_default.db')
    output = run_recorder(recorder, db, HELLOWORLD, idl=HELLOWORLD_IDL)

    if not os.path.exists(db):
        raise Failure('the recorder produced no database:\n' + output)

    checker.equal('processed 147 RTPS packets', packets(output), 147)
    checker.check('the recorder logged no error', not errors(output),
                  '; '.join(errors(output)[:3]))

    found = tables(db)
    checker.equal('exactly the 6 Record & Replay tables', found, MONITOR_TABLES)
    checker.check('none of the tables removed with TypeCode',
                  not (found & REMOVED_TABLES), 'found %s' % sorted(found & REMOVED_TABLES))
    checker.check('-queryable tables absent without the option',
                  not (found & QUERYABLE_TABLES),
                  'found %s' % sorted(found & QUERYABLE_TABLES))
    checker.check('the Messages index is created',
                  'Messages_topic_time' in indices(db), 'found %s' % sorted(indices(db)))

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

    # A raw RTPS fraction bound as nanoseconds would render 10 decimals, not 9, and could roll
    # the second over. Both the width and the distance below catch that.
    checker.check('log_time / publish_time are fixed-width with 9 decimals',
                  all(TIME_RE.match(r[8]) and TIME_RE.match(r[9]) for r in rows),
                  'e.g. %r / %r' % (rows[0][8], rows[0][9]) if rows else '')
    skewed = [r[1] for r in rows if seconds_between(r[8], r[9]) > 60]
    checker.check('publish_time stays within a minute of log_time '
                  '(catches a missed fraction->nanos conversion)',
                  not skewed, 'sequence numbers %s' % skewed[:5])

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
        checker.check('Types.idl holds the IDL read from the -idl file',
                      'struct HelloWorld' in (types[0][4] or ''),
                      'got %r' % (types[0][4],))
        checker.equal('Types.information stays empty (no XTypes on the wire)', types[0][1], '')
        checker.equal('Types.object stays empty (no XTypes on the wire)', types[0][2], '')

    checker.equal('Partitions holds the single empty partition',
                  query(db, 'SELECT name FROM Partitions'), [('',)])
    checker.equal('TopicsPartitions has 1 row',
                  one(db, 'SELECT COUNT(*) FROM TopicsPartitions'), 1)
    checker.equal('MessagesPartitions has 30 rows',
                  one(db, 'SELECT COUNT(*) FROM MessagesPartitions'), 30)


def check_no_idl(checker, recorder, workdir):
    """Without -idl the recording still happens; it just carries no type description."""
    print('\n== HelloWorld.pcap without -idl: recorded, but no type description ==')
    db = os.path.join(workdir, 'hw_noidl.db')
    output = run_recorder(recorder, db, HELLOWORLD)

    if not os.path.exists(db) or not (MONITOR_TABLES <= tables(db)):
        checker.check('the Record & Replay schema was produced', False)
        return

    checker.equal('processed 147 RTPS packets', packets(output), 147)
    checker.equal('Messages still has 30 rows', one(db, 'SELECT COUNT(*) FROM Messages'), 30)
    checker.equal('Types.idl is empty without -idl',
                  [r[0] for r in query(db, 'SELECT idl FROM Types')], [''])

    print('\n== HelloWorld.pcap with -queryable but no -idl: no data table ==')
    qdb = os.path.join(workdir, 'hw_q_noidl.db')
    run_recorder(recorder, qdb, HELLOWORLD, queryable=True)
    if os.path.exists(qdb) and QUERYABLE_TABLES <= tables(qdb):
        checker.equal('DataTables is empty', one(qdb, 'SELECT COUNT(*) FROM DataTables'), 0)
        checker.equal('Messages is still complete',
                      one(qdb, 'SELECT COUNT(*) FROM Messages'), 30)
        checker.check('no per-topic table was created',
                      not (tables(qdb) - MONITOR_TABLES - QUERYABLE_TABLES),
                      'found %s' % sorted(tables(qdb) - MONITOR_TABLES - QUERYABLE_TABLES))
    else:
        checker.check('the -queryable schema was produced without -idl', False)


def check_queryable_integrity(checker, db, name, expected_messages, expected_captures):
    """The -queryable tables must be consistent with the Record & Replay ones."""
    found = tables(db)
    checker.check('%s: Record & Replay tables kept beside the queryable ones' % name,
                  MONITOR_TABLES <= found,
                  'missing %s' % sorted(MONITOR_TABLES - found))
    checker.check('%s: the four queryable tables present' % name,
                  QUERYABLE_TABLES <= found,
                  'missing %s' % sorted(QUERYABLE_TABLES - found))
    if not (MONITOR_TABLES <= found and QUERYABLE_TABLES <= found):
        return

    checker.equal('%s: Messages rows' % name,
                  one(db, 'SELECT COUNT(*) FROM Messages'), expected_messages)
    checker.equal('%s: MessagesCapture rows (one per packet seen)' % name,
                  one(db, 'SELECT COUNT(*) FROM MessagesCapture'), expected_captures)
    checker.check('%s: MessagesCapture never loses a transmission' % name,
                  expected_captures >= expected_messages)

    # Referential integrity. Foreign keys are declared but not enforced, so check them here.
    dangling = one(db, 'SELECT COUNT(*) FROM MessagesCapture mc LEFT JOIN Messages m '
                       'USING (writer_guid, sequence_number) WHERE m.writer_guid IS NULL')
    checker.equal('%s: every MessagesCapture row points at a Messages row' % name, dangling, 0)

    dangling = one(db, 'SELECT COUNT(*) FROM Endpoints e LEFT JOIN Topics t '
                       'ON t.name = e.topic AND t.type = e.type WHERE t.name IS NULL')
    checker.equal('%s: every Endpoints row points at a Topics row' % name, dangling, 0)

    dangling = one(db, 'SELECT COUNT(*) FROM DiscoveryMessages d LEFT JOIN Endpoints e '
                       'ON e.guid = d.endpoint_guid WHERE e.guid IS NULL')
    checker.equal('%s: every DiscoveryMessages row points at an Endpoints row' % name,
                  dangling, 0)

    dangling = one(db, 'SELECT COUNT(*) FROM DataTables dt LEFT JOIN Topics t '
                       'ON t.name = dt.topic AND t.type = dt.type WHERE t.name IS NULL')
    checker.equal('%s: every DataTables row points at a Topics row' % name, dangling, 0)

    # Endpoints.guid is spelled like Messages.writer_guid, which is what makes them joinable.
    guids = [r[0] for r in query(db, 'SELECT guid FROM Endpoints')]
    checker.check('%s: Endpoints.guid uses the Messages.writer_guid format' % name,
                  guids and all(GUID_RE.match(g) for g in guids), 'got %s' % guids[:2])
    kinds = {r[0] for r in query(db, 'SELECT kind FROM Endpoints')}
    checker.check('%s: Endpoints.kind is DataWriter or DataReader' % name,
                  kinds <= {'DataWriter', 'DataReader'}, 'got %s' % sorted(kinds))
    checker.check('%s: every writer in Messages was announced' % name,
                  one(db, 'SELECT COUNT(*) FROM (SELECT DISTINCT writer_guid FROM Messages '
                          'EXCEPT SELECT guid FROM Endpoints)') == 0)

    prefixes = [r[0] for r in query(db, 'SELECT dst_guid_prefix FROM DiscoveryMessages '
                                        'WHERE dst_guid_prefix IS NOT NULL')]
    checker.check('%s: dst_guid_prefix is a bare GuidPrefix' % name,
                  all(PREFIX_RE.match(p) for p in prefixes), 'got %s' % prefixes[:2])

    checker.check('%s: the MessagesCapture index is created' % name,
                  'MessagesCapture_message' in indices(db))

    # Every table named in DataTables must exist, and have a flat view beside it.
    named = [r[0] for r in query(db, 'SELECT table_name FROM DataTables')]
    missing = [t for t in named if t not in found]
    checker.check('%s: every DataTables row names a table that exists' % name,
                  not missing, 'missing %s' % missing)
    present_views = views(db)
    viewless = [t for t in named if (t + '_flat') not in present_views]
    checker.check('%s: every data table has its _flat view' % name,
                  not viewless, 'missing views for %s' % viewless)

    # Every data row must anchor to a message.
    for table in named:
        orphans = one(db, 'SELECT COUNT(*) FROM "%s" d LEFT JOIN Messages m '
                          'USING (writer_guid, sequence_number) '
                          'WHERE m.writer_guid IS NULL' % table)
        if orphans:
            checker.check('%s: %s rows all anchor to Messages' % (name, table), False,
                          '%d orphan row(s)' % orphans)
            return
    checker.check('%s: every data row anchors to a Messages row' % name, True)


def check_helloworld_queryable(checker, recorder, workdir):
    print('\n== HelloWorld.pcap, -queryable ==')
    db = os.path.join(workdir, 'hw_queryable.db')
    output = run_recorder(recorder, db, HELLOWORLD, queryable=True, idl=HELLOWORLD_IDL)

    if not os.path.exists(db):
        raise Failure('the recorder produced no database:\n' + output)

    checker.equal('processed 147 RTPS packets', packets(output), 147)
    checker.check('the recorder logged no error', not errors(output),
                  '; '.join(errors(output)[:3]))

    check_queryable_integrity(checker, db, 'HelloWorld', 30, 31)

    if not (QUERYABLE_TABLES <= tables(db)):
        return

    checker.equal('exactly one duplicated transmission is kept',
                  one(db, 'SELECT COUNT(*) FROM (SELECT writer_guid, sequence_number '
                          'FROM MessagesCapture GROUP BY 1, 2 HAVING COUNT(*) > 1)'), 1)
    checker.equal('two endpoints announced', one(db, 'SELECT COUNT(*) FROM Endpoints'), 2)

    data = query(db, "SELECT table_name FROM DataTables WHERE member_path = ''")
    checker.equal('one root data table', len(data), 1)
    if data:
        table = data[0][0]
        checker.equal('the data table holds one row per message',
                      one(db, 'SELECT COUNT(*) FROM "%s"' % table), 30)
        columns = [d[1] for d in query(db, 'PRAGMA table_info("%s")' % table)]
        checker.equal('the data table is keyed on the message and holds the members',
                      columns, ['writer_guid', 'sequence_number', 'counter', 'message'])
        flat = [d[1] for d in query(db, 'PRAGMA table_info("%s_flat")' % table)]
        checker.equal('the flat view joins Messages back on',
                      flat[:4], ['log_time', 'publish_time', 'topic', 'type'])
        checker.equal('the flat view returns one row per message',
                      one(db, 'SELECT COUNT(*) FROM "%s_flat"' % table), 30)


def check_complextype_in_sequence(checker, recorder, workdir):
    """A sequence of a user type is representable now; it never was under TypeCode."""
    capture = os.path.join(CAPTURES, 'complextype_in_sequence.pcap')
    idl = capture_idl('complextype_in_sequence')
    if not os.path.exists(capture) or idl is None:
        return

    print('\n== complextype_in_sequence.pcap: a sequence of structs gets tables ==')
    db = os.path.join(workdir, 'cts_queryable.db')
    output = run_recorder(recorder, db, capture, queryable=True, idl=idl)

    if not os.path.exists(db):
        checker.check('the recorder produced a database', False)
        return

    checker.check('the recorder logged no error', not errors(output),
                  '; '.join(errors(output)[:3]))
    check_queryable_integrity(checker, db, 'complextype_in_sequence', 13, 13)

    if not (QUERYABLE_TABLES <= tables(db)):
        return

    rows = query(db, 'SELECT member_path, table_name FROM DataTables ORDER BY member_path')
    checker.equal('a root table and one for the sequence member',
                  [r[0] for r in rows], ['', 'seq'])
    if len(rows) == 2:
        root, child = rows[0][1], rows[1][1]
        checker.equal('the root table holds one row per message',
                      one(db, 'SELECT COUNT(*) FROM "%s"' % root), 13)
        columns = [d[1] for d in query(db, 'PRAGMA table_info("%s")' % root)]
        checker.equal('the root table holds only the key, the type has no scalar member',
                      columns, ['writer_guid', 'sequence_number'])
        child_columns = [d[1] for d in query(db, 'PRAGMA table_info("%s")' % child)]
        checker.equal('the element struct is flattened beside the index',
                      child_columns,
                      ['writer_guid', 'sequence_number', 'index_0', 'id', 'msg'])
        checker.check('the sequence elements were stored',
                      one(db, 'SELECT COUNT(*) FROM "%s"' % child) > 13,
                      'got %d' % one(db, 'SELECT COUNT(*) FROM "%s"' % child))


def check_unions(checker, recorder, workdir):
    """Every branch of a union must reach its own columns, chosen by the discriminator."""
    capture = os.path.join(CAPTURES, 'unions.pcap')
    idl = capture_idl('unions')
    if not os.path.exists(capture) or idl is None:
        return

    print('\n== unions.pcap: each branch reaches its own columns ==')
    db = os.path.join(workdir, 'unions_queryable.db')
    output = run_recorder(recorder, db, capture, queryable=True, idl=idl)

    if not os.path.exists(db):
        checker.check('the recorder produced a database', False)
        return

    checker.check('the recorder logged no error', not errors(output),
                  '; '.join(errors(output)[:3]))
    check_queryable_integrity(checker, db, 'unions', 47, 47)

    if not (QUERYABLE_TABLES <= tables(db)):
        return

    root = query(db, "SELECT table_name FROM DataTables WHERE member_path = ''")
    if not root:
        checker.check('unions has a root data table', False)
        return
    table = root[0][0]

    checker.equal('every message reached the data table',
                  one(db, 'SELECT COUNT(*) FROM "%s"' % table), 47)

    columns = [d[1] for d in query(db, 'PRAGMA table_info("%s")' % table)]
    checker.check('the discriminator has a column of its own',
                  'u_n_i_o_n_discriminator' in columns, 'got %s' % columns)

    branches = query(db, 'SELECT u_n_i_o_n_discriminator, COUNT(*) FROM "%s" '
                         'GROUP BY 1 ORDER BY 1' % table)
    checker.check('more than one branch was taken', len(branches) > 1,
                  'got %s' % branches)
    checker.equal('the branch counts add up to the message count',
                  sum(r[1] for r in branches), 47)

    # A row must fill the columns of the branch it took and leave the others NULL.
    mixed = one(db, 'SELECT COUNT(*) FROM "%s" '
                    'WHERE u_n_i_o_n_message IS NOT NULL '
                    'AND u_n_i_o_n_ins_ulo IS NOT NULL' % table)
    checker.equal('no row fills two branches at once', mixed, 0)


def check_idl_metadata(checker, recorder, workdir):
    """shapes.pcapng is the capture kept for the -idl path; it carries no type at all."""
    capture = os.path.join(REPO, 'shapes.pcapng')
    idl = os.path.join(REPO, 'Shape.idl')
    if not (os.path.exists(capture) and os.path.exists(idl)):
        print('\n== shapes.pcapng / Shape.idl absent, skipping the -idl metadata check ==')
        return

    print('\n== shapes.pcapng: -idl fills Types.idl ==')
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

    checker.equal('Types.idl is empty without -idl',
                  [r[0] for r in query(without, "SELECT idl FROM Types "
                                                "WHERE name = 'ShapeType'")], [''])

    info_with = query(withidl, "SELECT idl, information FROM Types WHERE name = 'ShapeType'")
    checker.equal('Types row for ShapeType exists with -idl', len(info_with), 1)
    if info_with:
        checker.check('Types.idl holds the IDL from the file',
                      'struct ShapeType' in (info_with[0][0] or ''),
                      'got %r' % (info_with[0][0],))
        checker.equal('Types.information stays empty even with -idl',
                      info_with[0][1], '')

    checker.equal('the two runs agree on the topic set',
                  one(without, 'SELECT COUNT(*) FROM Topics'),
                  one(withidl, 'SELECT COUNT(*) FROM Topics'))


# name -> (Messages rows, MessagesCapture rows)
REMAINING = {
    'basic_types': (25, 25),
    'recursive_structs': (10, 10),
    'test1': (3, 9),
    'test2': (9, 9),
    'arrays': (23, 23),
    'sequences': (20, 20),
}

# These two build twenty child tables each and are much slower than the rest.
SLOW = {'arrays', 'sequences'}


def check_remaining_fixtures(checker, recorder, workdir, quick):
    print('\n== remaining fixtures, both schemas ==')
    for name in sorted(REMAINING):
        if quick and name in SLOW:
            print('  skip %s (--quick)' % name)
            continue

        capture = os.path.join(CAPTURES, name + '.pcap')
        idl = capture_idl(name)
        if not os.path.exists(capture):
            continue
        checker.check('%s: an IDL file sits beside the capture' % name, idl is not None)
        if idl is None:
            continue

        expected_messages, expected_captures = REMAINING[name]

        db = os.path.join(workdir, name + '_default.db')
        output = run_recorder(recorder, db, capture, idl=idl)
        if not os.path.exists(db) or not (MONITOR_TABLES <= tables(db)):
            checker.check('%s: the Record & Replay schema was produced' % name, False)
            continue
        checker.check('%s: the default run logged no error' % name, not errors(output),
                      '; '.join(errors(output)[:2]))
        checker.equal('%s: Messages rows in the default schema' % name,
                      one(db, 'SELECT COUNT(*) FROM Messages'), expected_messages)
        checker.equal('%s: every CDR blob is consistent' % name,
                      one(db, 'SELECT COUNT(*) FROM Messages '
                              'WHERE data_cdr_size != length(data_cdr) '
                              'OR data_cdr_size <= 0'), 0)

        qdb = os.path.join(workdir, name + '_queryable.db')
        qoutput = run_recorder(recorder, qdb, capture, queryable=True, idl=idl)
        if not os.path.exists(qdb):
            checker.check('%s: the queryable schema was produced' % name, False)
            continue
        checker.check('%s: the queryable run logged no error' % name, not errors(qoutput),
                      '; '.join(errors(qoutput)[:2]))
        check_queryable_integrity(checker, qdb, name, expected_messages, expected_captures)
        checker.check('%s: at least one data table was created' % name,
                      one(qdb, 'SELECT COUNT(*) FROM DataTables') > 0)


def main(argv=None):
    parser = argparse.ArgumentParser(
        description='Check the database schema of the Non-Intrusive DDS Recorder.')
    parser.add_argument('-r', '--recorder',
                        default=os.environ.get('DDS_RECORDER', 'dds_recorder'),
                        help='path to the dds_recorder binary '
                             '(default: $DDS_RECORDER or dds_recorder on PATH)')
    parser.add_argument('-k', '--keep', action='store_true',
                        help='keep the generated databases for inspection')
    parser.add_argument('-q', '--quick', action='store_true',
                        help='skip arrays and sequences, which are slow to record')
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
    workdir = tempfile.mkdtemp(prefix='schema_check_')
    try:
        check_helloworld_default(checker, recorder, workdir)
        check_no_idl(checker, recorder, workdir)
        check_helloworld_queryable(checker, recorder, workdir)
        check_complextype_in_sequence(checker, recorder, workdir)
        check_unions(checker, recorder, workdir)
        check_idl_metadata(checker, recorder, workdir)
        check_remaining_fixtures(checker, recorder, workdir, args.quick)
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
