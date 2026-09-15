#!/usr/bin/env python3
"""Check the -mcap output of the Non-Intrusive DDS Recorder.

The recorder has no C++ test suite, so this script is the regression check for the MCAP
output.  It records the fixture captures with -mcap and to a database, then validates the
MCAP file and compares it against the SQLite recording, which is the already-verified path
and therefore a usable oracle.

The MCAP file is read with the independent `mcap` package from PyPI rather than with the
vendored C++ library, so the writer is not being checked with its own code.  Install it with
`pip install mcap`; the script reports and skips if it is absent.

The recorder returns the same non-zero exit status on success and on failure, so the exit
status is never consulted; stdout and the resulting files are.
"""

import argparse
import base64
import glob
import hashlib
import os
import re
import shutil
import sqlite3
import struct
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CAPTURES = os.path.join(REPO, 'utils', 'pcTests', 'capturefiles')
HELLOWORLD = os.path.join(REPO, 'examples', 'HelloWorld', 'HelloWorld.pcap')
HELLOWORLD_IDL = os.path.join(REPO, 'examples', 'HelloWorld', 'HelloWorld.idl')

GUID_RE = re.compile(r'^([0-9a-f]{2}\.){11}[0-9a-f]{2}\|[0-9a-f]{1,2}(\.[0-9a-f]{1,2}){3}$')

# Record & Replay names these; see ddsrecorder_participants/include/.../constants.hpp
DYNAMIC_TYPES_ATTACHMENT = 'dynamic_types'
DEPENDENCY_PREFIX = '__dep__/'
METADATA_GUID = 'messages_guid'
METADATA_GUID_INDEX = 'messages_guid_index'
METADATA_VERSION = 'version'
CHANNEL_QOS = 'qos'
CHANNEL_ROS2 = 'ros2-types'
CHANNEL_PARTITIONS = 'partitions'


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


def run_recorder(recorder, capture, db=None, mcap=None, idl=None):
    command = [recorder]
    if db:
        command += ['-db', db]
    if mcap:
        command += ['-mcap', mcap]
    if idl:
        command += ['-idl', idl]
    command.append(capture)
    done = subprocess.run(command, capture_output=True, text=True)
    return done.stdout + done.stderr


def mcap_supported(recorder):
    """Whether this build has the MCAP writer compiled in.

    MCAP_SUPPORT is a build-time option, and a build without it omits -mcap from the help and
    refuses the argument, so the help text is the way to ask.
    """
    done = subprocess.run([recorder, '-help'], capture_output=True, text=True)
    return '-mcap' in (done.stdout + done.stderr)


def read_mcap(path):
    """Return (header, schemas, channels, messages, metadata) using the PyPI reader."""
    from mcap.reader import make_reader

    with open(path, 'rb') as handle:
        reader = make_reader(handle)
        summary = reader.get_summary()
        header = reader.get_header()
        messages = []
        for schema, channel, message in reader.iter_messages():
            messages.append({
                'topic': channel.topic,
                'message_encoding': channel.message_encoding,
                'channel_metadata': dict(channel.metadata),
                'schema_name': schema.name if schema else None,
                'schema_encoding': schema.encoding if schema else None,
                'schema_data': bytes(schema.data).decode('utf-8', 'replace') if schema else '',
                'sequence': message.sequence,
                'log_time': message.log_time,
                'publish_time': message.publish_time,
                'data': bytes(message.data),
            })
        metadata = {}
        # Metadata records live in the data section; re-read the stream for them.
        handle.seek(0)
        from mcap.reader import NonSeekingReader
        for record in NonSeekingReader(handle).iter_metadata():
            metadata[record.name] = dict(record.metadata)

    schemas = {s.name: s for s in (summary.schemas.values() if summary else [])}
    channels = {c.topic: c for c in (summary.channels.values() if summary else [])}
    return header, schemas, channels, messages, metadata


def monitor_rows(recorder, capture, workdir, name, idl=None):
    """Record the same capture to a database and return its Messages rows."""
    db = os.path.join(workdir, name + '_monitor.db')
    run_recorder(recorder, capture, db=db, idl=idl)
    if not os.path.exists(db):
        return None, None
    connection = sqlite3.connect('file:%s?mode=ro' % db, uri=True)
    try:
        rows = list(connection.execute(
            'SELECT writer_guid, sequence_number, data_cdr, log_time, publish_time, '
            'topic, type FROM Messages ORDER BY sequence_number'))
        types = list(connection.execute('SELECT name, idl FROM Types'))
        return rows, types
    finally:
        connection.close()


def sql_time_to_nanos(text):
    """'YYYY-MM-DD HH:MM:SS.nnnnnnnnn' (UTC) -> nanoseconds since the epoch."""
    import calendar
    import datetime
    stamp, fraction = text.split('.')
    moment = datetime.datetime.strptime(stamp, '%Y-%m-%d %H:%M:%S')
    return calendar.timegm(moment.timetuple()) * 1000000000 + int(fraction)


def read_attachments(path):
    """The attachments of an MCAP file, by name."""
    from mcap.reader import NonSeekingReader
    with open(path, 'rb') as handle:
        return {record.name: bytes(record.data)
                for record in NonSeekingReader(handle).iter_attachments()}


def decode_dynamic_types(data):
    """The types the 'dynamic_types' attachment holds, as (name, identifier, object) triples.

    The attachment is the CDR of the DynamicTypesCollection of *DDS Record & Replay*: a sequence
    of three strings apiece, XCDRv1, behind the four byte encapsulation header whose second byte
    says the endianness. Decoded by hand rather than with Fast DDS, so that the writer is not
    checked with the library that produced it.
    """
    endian = '<' if data[1] & 1 else '>'
    body, offset, types = data[4:], 0, []
    count = struct.unpack_from(endian + 'I', body, offset)[0]
    offset += 4

    for _ in range(count):
        entry = []
        for _ in range(3):
            offset += -offset % 4                       # CDR aligns a length to four bytes
            length = struct.unpack_from(endian + 'I', body, offset)[0]
            offset += 4
            entry.append(body[offset:offset + length - 1].decode('utf-8'))  # length counts the NUL
            offset += length
        types.append(tuple(entry))

    return types


def hashes_to(identifier, type_object):
    """Whether the TypeIdentifier is the hash of the TypeObject, as XTypes defines it.

    The equivalence hash is the first 14 bytes of the MD5 of the serialized TypeObject, taken
    before the padding the recorder adds, so the four possible paddings are tried. This ties the
    two strings of an entry together without trusting anything that produced them.
    """
    if len(identifier) != 16 or not type_object:
        return False
    return any(hashlib.md5(type_object[:len(type_object) - trim]).digest()[:14] == identifier[1:15]
               for trim in range(4))


def monitor_types(recorder, capture, workdir, name, idl=None):
    """Record the same capture to a database and return its Types rows, the oracle."""
    db = os.path.join(workdir, name + '_types.db')
    run_recorder(recorder, capture, db=db, idl=idl)
    if not os.path.exists(db):
        return None
    connection = sqlite3.connect('file:%s?mode=ro' % db, uri=True)
    try:
        return list(connection.execute('SELECT name, information, object FROM Types'))
    finally:
        connection.close()


def check_dynamic_types(checker, recorder, workdir):
    """The data types are stored in the attachment DDS Record & Replay keeps them in.

    An MCAP file has no table of types: they live in one attachment, as the CDR of a collection of
    (type name, TypeIdentifier, TypeObject) triples. The SQLite Types table of the same capture is
    the oracle, being the path this suite has already verified.
    """
    print('\n== the data types are stored in the dynamic_types attachment ==')

    fixtures = [('HelloWorld', HELLOWORLD, HELLOWORLD_IDL)]
    for name in ('recursive_structs', 'complextype_in_sequence'):
        fixtures.append((name, os.path.join(CAPTURES, name + '.pcap'),
                         os.path.join(CAPTURES, name + '.idl')))

    for name, capture, idl in fixtures:
        if not (os.path.exists(capture) and os.path.exists(idl)):
            checker.check('%s: the fixture is present' % name, False)
            continue

        path = os.path.join(workdir, name + '_types.mcap')
        run_recorder(recorder, capture, mcap=path, idl=idl)

        if not os.path.exists(path):
            checker.check('%s: produced an MCAP file' % name, False)
            continue

        attachments = read_attachments(path)
        checker.equal('%s: one attachment, named %s' % (name, DYNAMIC_TYPES_ATTACHMENT),
                      sorted(attachments), [DYNAMIC_TYPES_ATTACHMENT])

        if DYNAMIC_TYPES_ATTACHMENT not in attachments:
            continue

        types = decode_dynamic_types(attachments[DYNAMIC_TYPES_ATTACHMENT])

        # The database recording of the same capture holds the same three columns.
        expected = monitor_types(recorder, capture, workdir, name, idl=idl)
        if expected is None:
            checker.check('%s: the database run produced a database' % name, False)
            continue

        checker.equal('%s: the attachment holds exactly what the Types table holds' % name,
                      sorted(types), sorted(expected))

        bad = [entry[0] for entry in types
               if not hashes_to(base64.b64decode(entry[1]), base64.b64decode(entry[2]))]
        checker.check('%s: every TypeIdentifier is the hash of the TypeObject beside it' % name,
                      not bad, 'types %s' % bad[:3])

        bad = [entry[0] for entry in types
               if entry[0].startswith(DEPENDENCY_PREFIX) and entry[0] != DEPENDENCY_PREFIX + entry[1]]
        checker.check('%s: every dependency is keyed by its own TypeIdentifier' % name, not bad,
                      'entries %s' % bad[:3])

    # A type has to come from somewhere: without -idl there is nothing to put in an attachment.
    path = os.path.join(workdir, 'noidl_types.mcap')
    run_recorder(recorder, HELLOWORLD, mcap=path)
    if os.path.exists(path):
        checker.equal('without -idl the file carries no attachment',
                      sorted(read_attachments(path)), [])


def check_helloworld(checker, recorder, workdir):
    print('\n== HelloWorld.pcap, -mcap ==')
    path = os.path.join(workdir, 'hw.mcap')
    # -idl is the only source of data types, so the schema records stay empty without it.
    output = run_recorder(recorder, HELLOWORLD, mcap=path, idl=HELLOWORLD_IDL)

    if not os.path.exists(path):
        raise Failure('the recorder produced no MCAP file:\n' + output)

    checker.check('the file starts with the MCAP magic',
                  open(path, 'rb').read(5) == b'\x89MCAP')

    header, schemas, channels, messages, metadata = read_mcap(path)

    checker.equal('profile is empty', header.profile, '')
    checker.check('library is set', bool(header.library), 'got %r' % header.library)

    checker.equal('one schema', sorted(schemas), ['HelloWorld'])
    if 'HelloWorld' in schemas:
        schema = schemas['HelloWorld']
        checker.equal('schema encoding is omgidl', schema.encoding, 'omgidl')
        checker.check('schema data holds the IDL',
                      'struct HelloWorld' in bytes(schema.data).decode('utf-8', 'replace'),
                      'got %r' % bytes(schema.data)[:60])

    checker.equal('one channel, topic verbatim', sorted(channels), ['Example HelloWorld'])
    if 'Example HelloWorld' in channels:
        channel = channels['Example HelloWorld']
        checker.equal('channel encoding is cdr', channel.message_encoding, 'cdr')
        keys = dict(channel.metadata)
        checker.check('channel metadata carries qos/ros2-types/partitions',
                      {CHANNEL_QOS, CHANNEL_ROS2, CHANNEL_PARTITIONS} <= set(keys),
                      'got %s' % sorted(keys))
        checker.equal('ros2-types is false', keys.get(CHANNEL_ROS2), 'false')
        checker.check('qos is the 4-key default',
                      keys.get(CHANNEL_QOS, '').startswith('reliability:'),
                      'got %r' % keys.get(CHANNEL_QOS))

    checker.equal('30 messages (31 transmissions, 1 duplicate)', len(messages), 30)
    checker.equal('sequence is a gap-free range from 0',
                  sorted(m['sequence'] for m in messages), list(range(30)))

    # The GUID is recovered in two hops, exactly as mcap-convert does it.
    guid_map = metadata.get(METADATA_GUID, {})
    index_map = metadata.get(METADATA_GUID_INDEX, {})
    checker.check('both guid metadata records are present',
                  bool(guid_map) and bool(index_map),
                  'messages_guid=%d entries, messages_guid_index=%d entries'
                  % (len(guid_map), len(index_map)))
    resolved = {index_map.get(guid_map.get(str(m['sequence']))) for m in messages}
    checker.equal('every message resolves to the expected writer GUID',
                  sorted(x for x in resolved if x),
                  ['c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3'])
    checker.check('the GUID has the Fast DDS text format',
                  all(GUID_RE.match(x) for x in resolved if x))
    checker.check('a version metadata record is present',
                  METADATA_VERSION in metadata, 'got %s' % sorted(metadata))

    # -- cross-format equivalence against the verified SQLite path -------------
    print('\n== HelloWorld.pcap, -mcap vs the database ==')
    rows, types = monitor_rows(recorder, HELLOWORLD, workdir, 'hw', idl=HELLOWORLD_IDL)
    if rows is None:
        checker.check('the database run produced a database', False)
        return

    checker.equal('same message count as the database', len(messages), len(rows))
    checker.equal('payloads match byte for byte, as a multiset',
                  sorted(m['data'] for m in messages),
                  sorted(r[2] for r in rows))
    checker.equal('log_time matches to the nanosecond',
                  sorted(m['log_time'] for m in messages),
                  sorted(sql_time_to_nanos(r[3]) for r in rows))
    checker.equal('publish_time matches to the nanosecond',
                  sorted(m['publish_time'] for m in messages),
                  sorted(sql_time_to_nanos(r[4]) for r in rows))
    checker.equal('topic and type agree',
                  sorted({(m['topic'], m['schema_name']) for m in messages}),
                  sorted({(r[5], r[6]) for r in rows}))
    if types:
        checker.equal('schema data equals Types.idl',
                      bytes(schemas['HelloWorld'].data).decode('utf-8', 'replace'),
                      types[0][1])


def check_untyped_and_counts(checker, recorder, workdir):
    print('\n== every fixture: -mcap message count equals the database row count ==')
    fixtures = [HELLOWORLD] + sorted(glob.glob(os.path.join(CAPTURES, '*.pcap')))
    for capture in fixtures:
        name = os.path.splitext(os.path.basename(capture))[0]
        path = os.path.join(workdir, name + '.mcap')
        run_recorder(recorder, capture, mcap=path)
        if not os.path.exists(path):
            checker.check('%s: produced an MCAP file' % name, False)
            continue
        try:
            _, _, _, messages, _ = read_mcap(path)
        except Exception as error:
            checker.check('%s: file is readable' % name, False, str(error))
            continue
        rows, _ = monitor_rows(recorder, capture, workdir, name)
        expected = len(rows) if rows is not None else None
        checker.equal('%s: %d message(s)' % (name, len(messages)), len(messages), expected)
        checker.check('%s: every payload is non-empty' % name,
                      all(len(m['data']) > 0 for m in messages))

    # complextype_in_sequence has no usable type, so the default schema stores nothing at all.
    path = os.path.join(workdir, 'complextype_in_sequence.mcap')
    if os.path.exists(path):
        _, _, _, messages, _ = read_mcap(path)
        checker.equal('complextype_in_sequence: 13 messages despite having no usable type',
                      len(messages), 13)


def check_idl_metadata(checker, recorder, workdir):
    """The Shapes capture, recorded to MCAP with and without -idl.

    It is the fixture that separates the schema from the recording. The samples are stored as
    their raw CDR either way, so -idl changes nothing but the omgidl text the schema records
    carry, and the two files must hold the same messages. Shape.idl declares ShapeType and
    nothing else, while the capture also announces the Fast DDS statistics topics, so those are
    the case that has to keep an empty schema even on the run that was given an IDL file. Most of
    them are announced and never written to, which is also what makes this the fixture where a
    channel has to exist for a topic that carries no sample at all.
    """
    capture = os.path.join(CAPTURES, 'shape.pcapng')
    idl = os.path.join(CAPTURES, 'Shape.idl')
    if not (os.path.exists(capture) and os.path.exists(idl)):
        checker.check('shape: the fixture is present: shape.pcapng, Shape.idl', False)
        return

    print('\n== shape.pcapng: -idl fills the schema data ==')
    without = os.path.join(workdir, 'shape_noidl.mcap')
    withidl = os.path.join(workdir, 'shape_idl.mcap')
    run_recorder(recorder, capture, mcap=without)
    run_recorder(recorder, capture, mcap=withidl, idl=idl)

    # The SQLite recording of the same capture is the oracle here, as it is everywhere else in
    # this script: it is the path check_monitor_schema.py has already verified.
    rows, _ = monitor_rows(recorder, capture, workdir, 'shape', idl=idl)
    if rows is None:
        checker.check('shape: the database the MCAP file is compared against was produced',
                      False)
        return
    expected = {}
    for row in rows:
        expected[row[5]] = expected.get(row[5], 0) + 1

    for path, label, expect_idl in ((without, 'without -idl', False),
                                    (withidl, 'with -idl', True)):
        if not os.path.exists(path):
            checker.check('%s: produced an MCAP file' % label, False)
            continue
        _, schemas, channels, messages, _ = read_mcap(path)

        actual = {}
        for message in messages:
            actual[message['topic']] = actual.get(message['topic'], 0) + 1
        checker.equal('%s: the messages match the database, topic by topic' % label,
                      actual, expected)

        # Every topic gets a channel, whether or not a sample of it was ever captured. Both
        # operands come from the recording: the announced topics are the channels, the ones
        # carrying a sample are what the database counted.
        checker.check('%s: a channel exists for every topic that carries a sample' % label,
                      set(expected) <= set(channels),
                      'missing %s' % sorted(set(expected) - set(channels)))
        checker.check('%s: the announced but silent topics get a channel too' % label,
                      len(set(channels) - set(expected)) > 0,
                      'channels: %s' % sorted(channels)[:4])

        checker.equal('%s: every schema is declared omgidl' % label,
                      sorted({schema.encoding for schema in schemas.values()}), ['omgidl'])

        if 'ShapeType' not in schemas:
            checker.check('%s: the ShapeType schema is recorded' % label, False,
                          'schemas: %s' % sorted(schemas)[:4])
            continue
        data = bytes(schemas['ShapeType'].data).decode('utf-8', 'replace')

        # A schema record with no data is how a type the recorder could not describe is written;
        # the IDL file is the only thing that fills it in.
        filled = sorted(name for name, schema in schemas.items() if bytes(schema.data))
        if expect_idl:
            checker.check('%s: schema data holds the IDL from the file' % label,
                          'struct ShapeType' in data, 'got %r' % data[:60])
            checker.check('%s: the @key annotation survives into the schema' % label,
                          '@key' in data, 'got %r' % data[:120])
            # Shape.idl declares ShapeType alone, so every other type announced by the capture
            # keeps the empty schema it would have had with no IDL file at all.
            checker.equal('%s: only the type the IDL file declares is described' % label,
                          filled, ['ShapeType'])
        else:
            checker.equal('%s: schema data is empty' % label, data, '')
            checker.equal('%s: no schema carries data at all' % label, filled, [])


def check_mutual_exclusion(checker, recorder, workdir):
    print('\n== -db and -mcap together are refused ==')
    db = os.path.join(workdir, 'both.db')
    mcap = os.path.join(workdir, 'both.mcap')
    output = run_recorder(recorder, HELLOWORLD, db=db, mcap=mcap)
    checker.check('the run is rejected with a message naming both options',
                  '-db' in output and '-mcap' in output,
                  'output was %r' % output[:200])
    checker.check('neither output file is created',
                  not os.path.exists(db) and not os.path.exists(mcap),
                  'db=%s mcap=%s' % (os.path.exists(db), os.path.exists(mcap)))


def main(argv=None):
    parser = argparse.ArgumentParser(
        description='Check the -mcap output of the Non-Intrusive DDS Recorder.')
    parser.add_argument('-r', '--recorder',
                        default=os.environ.get('DDS_RECORDER', 'ni_ddsrecorder'),
                        help='path to the ni_ddsrecorder binary')
    parser.add_argument('-k', '--keep', action='store_true',
                        help='keep the generated files for inspection')
    args = parser.parse_args(argv)

    try:
        import mcap.reader  # noqa: F401
    except ImportError:
        print('error: the `mcap` package is required to validate the output '
              'independently of our own writer.\n       Install it with: pip install mcap',
              file=sys.stderr)
        return 2

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

    if not mcap_supported(recorder):
        print('\nSKIPPED: this build has no MCAP support (built with -DMCAP_SUPPORT=OFF, or\n'
              '         with AUTO and no lz4/zstd headers). Nothing to check.')
        output = run_recorder(recorder, HELLOWORLD, mcap=os.path.join(
            tempfile.gettempdir(), 'unsupported.mcap'))
        if 'MCAP support' in output:
            print('         -mcap is refused with a clear message, as it should be.')
            return 0
        print('error: -mcap should have been refused with a message naming MCAP support,\n'
              '       but the recorder said: %r' % output[:200], file=sys.stderr)
        return 1

    checker = Checker()
    workdir = tempfile.mkdtemp(prefix='mcap_output_')
    try:
        check_helloworld(checker, recorder, workdir)
        check_untyped_and_counts(checker, recorder, workdir)
        check_idl_metadata(checker, recorder, workdir)
        check_dynamic_types(checker, recorder, workdir)
        check_mutual_exclusion(checker, recorder, workdir)
    except Failure as failure:
        print('\nABORTED: %s' % failure, file=sys.stderr)
        return 1
    finally:
        if args.keep:
            print('\nfiles kept in %s' % workdir)
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
