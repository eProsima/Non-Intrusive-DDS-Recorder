.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_querying_database:

##############################
Querying the recorded database
##############################

The output of |eddsrecorder| is an ordinary :term:`SQLite` file, so any tool able to read one can analyze a recorded
session: the ``sqlite3`` command line client, a GUI such as `SQLiteman <http://sqliteman.com/>`_, or the SQLite
bindings of your favorite programming language.

This section collects queries that answer the questions that come up most often when inspecting a capture.
All of them run against the ``HelloWorld`` example described in :ref:`user_manual_usage_example`, whose topic
``Example HelloWorld`` is stored in the table ``Data_Example_HelloWorld``.

.. note::

    These recipes are written for the ``-queryable`` schema, whose per-topic tables they join and
    filter. For the default schema, whose payload is an opaque blob until something decodes it, see
    :ref:`user_manual_monitor_schema_querying`.

To follow along, open the database with:

.. code-block:: bash

    sqlite3 HelloWorld-queryable.db

The examples below are shown with the column headers enabled, which the client turns on with
``.headers on`` and ``.mode column``.

.. _user_manual_querying_database_exploring:

**********************
Exploring the database
**********************

Listing the recorded topics
===========================

Every DDS Topic seen in the discovery traffic appears in ``Topics``, and ``Endpoints`` holds the DataWriters and
DataReaders announced for it:

.. code-block:: sql

    SELECT t.name, t.type,
           (SELECT COUNT(*) FROM Endpoints e
             WHERE e.topic = t.name AND e.kind = 'DataWriter') AS writers,
           (SELECT COUNT(*) FROM Endpoints e
             WHERE e.topic = t.name AND e.kind = 'DataReader') AS readers
    FROM Topics t;

.. code-block:: text

    name                type        writers  readers
    ------------------  ----------  -------  -------
    Example HelloWorld  HelloWorld  1        1

Listing the tables that hold samples
====================================

``DataTables`` names them, so the mangling that turns a topic name into an SQL identifier never has to be reproduced
by hand.  The row whose ``member_path`` is empty is the topic's own table:

.. code-block:: sql

    SELECT topic, table_name FROM DataTables WHERE member_path = '' ORDER BY topic;

.. code-block:: text

    topic               table_name
    ------------------  -----------------------
    Example HelloWorld  Data_Example_HelloWorld

A topic that is in ``Topics`` but not in ``DataTables`` was recorded without being deserialized, which happens when no
IDL file described its type:

.. code-block:: sql

    SELECT t.name, t.type FROM Topics t
     WHERE NOT EXISTS (SELECT 1 FROM DataTables d
                        WHERE d.topic = t.name AND d.type = t.type);

Its samples are still in ``Messages``, as :term:`CDR`.

Reading the data type of a topic
================================

``Types`` holds the IDL rendering of the type, taken from the file given with ``-idl``:

.. code-block:: sql

    SELECT idl FROM Types WHERE name = 'HelloWorld';

.. code-block:: idl

    @extensibility(APPENDABLE)
    struct HelloWorld
    {
        long counter;
        string message;
    };

An empty ``idl`` column means no IDL file described that type.

.. _user_manual_querying_database_entities:

***********************
Inspecting the entities
***********************

Listing the endpoints
=====================

``Endpoints`` stores each :term:`Guid` in the same text notation as ``Messages.writer_guid``, so no formatting is
needed and the two tables join directly:

.. code-block:: sql

    SELECT guid, kind, topic FROM Endpoints ORDER BY topic, kind;

.. code-block:: text

    guid                                          kind        topic
    --------------------------------------------  ----------  ------------------
    c0.a8.44.05.00.00.15.98.00.00.00.01|80.0.0.4  DataReader  Example HelloWorld
    c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3  DataWriter  Example HelloWorld

Counting how many samples each writer sent is then a plain join:

.. code-block:: sql

    SELECT e.kind, e.topic, COUNT(m.sequence_number) AS samples
      FROM Endpoints e LEFT JOIN Messages m ON m.writer_guid = e.guid
     GROUP BY e.guid;

Finding topics that need an IDL file
====================================

|eddsrecorder| reads no type description from the wire, so a type is described only when ``-idl`` supplied it.
This query lists the types that were not:

.. code-block:: sql

    SELECT name FROM Types WHERE idl = '';

An empty result, which is the case in the example, means every type was described.

Seeing the packets behind the samples
=====================================

``Messages`` describes the recording as a DDS application would see it.
``MessagesCapture`` describes it as the sniffer did, one row per packet, so the two differ whenever a sample
traveled more than once:

.. code-block:: sql

    SELECT m.topic,
           COUNT(DISTINCT mc.packet_id) AS packets,
           COUNT(DISTINCT m.sequence_number) AS samples
      FROM Messages m JOIN MessagesCapture mc USING (writer_guid, sequence_number)
     GROUP BY m.topic;

.. code-block:: text

    topic               packets  samples
    ------------------  -------  -------
    Example HelloWorld  31       30

The repetitions themselves:

.. code-block:: sql

    SELECT writer_guid, sequence_number, COUNT(*) AS transmissions
      FROM MessagesCapture GROUP BY 1, 2 HAVING COUNT(*) > 1;

.. code-block:: text

    writer_guid                                   sequence_number  transmissions
    --------------------------------------------  ---------------  -------------
    c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3  1                2

.. _user_manual_querying_database_samples:

*********************
Analyzing the samples
*********************

A topic table holds the members of the data type and the key back into ``Messages``; everything else lives in
``Messages`` and ``MessagesCapture``.
The queries below join them explicitly, but the ``_flat`` view created next to each table already does the
``Messages`` half:

.. code-block:: sql

    SELECT log_time, counter, message FROM Data_Example_HelloWorld_flat ORDER BY log_time;

Listing samples in capture order
================================

``MessagesCapture.packet_id`` is the packet number in the capture file, so ordering by it reproduces the order in
which the traffic was observed, repetitions included:

.. code-block:: sql

    SELECT mc.packet_id, mc.log_time, d.counter, d.message
      FROM MessagesCapture mc
      JOIN Data_Example_HelloWorld d USING (writer_guid, sequence_number)
     ORDER BY mc.packet_id
     LIMIT 4;

.. code-block:: text

    packet_id  log_time                       counter  message
    ---------  -----------------------------  -------  ------------
    38         2013-06-18 13:08:52.160848000  0        HelloWorld 0
    45         2013-06-18 13:08:52.324946000  0        HelloWorld 0
    55         2013-06-18 13:08:56.162000000  1        HelloWorld 1
    59         2013-06-18 13:09:00.163239000  2        HelloWorld 2

Detecting repeated samples
==========================

The same sample often appears more than once in a capture, because it was sent to several destinations or
retransmitted.
``Messages`` holds it once; joining ``MessagesCapture`` counts the transmissions:

.. code-block:: sql

    SELECT d.counter, COUNT(*) AS transmissions,
           MIN(mc.packet_id) AS first_packet, MAX(mc.packet_id) AS last_packet
      FROM Data_Example_HelloWorld d
      JOIN MessagesCapture mc USING (writer_guid, sequence_number)
     GROUP BY d.counter
    HAVING COUNT(*) > 1
     ORDER BY d.counter;

.. code-block:: text

    counter  transmissions  first_packet  last_packet
    -------  -------------  ------------  -----------
    0        2              38            45

.. note::

    This is the difference between the two tables.
    A row of ``Messages`` is a sample the application wrote; a row of ``MessagesCapture`` is a packet the sniffer saw.
    Count the first to answer "how many samples", the second to answer "how much traffic".

Measuring the publication period
================================

``log_time`` is text, so convert it before subtracting.
``julianday`` accepts three decimals, which is millisecond resolution:

.. code-block:: sql

    SELECT packet_id,
           CAST((julianday(substr(log_time, 1, 23)) -
                 LAG(julianday(substr(log_time, 1, 23))) OVER (ORDER BY packet_id))
                * 86400000 AS INTEGER) AS delta_ms
      FROM MessagesCapture
     ORDER BY packet_id
     LIMIT 5;

.. code-block:: text

    packet_id  delta_ms
    ---------  --------
    38
    45         163
    55         3837
    59         4001
    62         4000

The publisher writes every four seconds; the much shorter first interval is the second transmission of sample ``0``
identified above.

Comparing the source clock against the capture clock
====================================================

Each sample carries two timestamps: ``publish_time``, written by the publishing participant with its own clock, and
``log_time``, added by the sniffer.
Their difference mixes clock offset with time in flight, which makes it a practical way to spot nodes whose clocks
are not synchronized:

.. code-block:: sql

    SELECT sequence_number,
           CAST((julianday(substr(log_time, 1, 23)) -
                 julianday(substr(publish_time, 1, 23))) * 86400000 AS INTEGER) AS skew_ms
      FROM Messages
     ORDER BY sequence_number
     LIMIT 4;

.. code-block:: text

    sequence_number  skew_ms
    ---------------  -------
    1                0
    2                2
    3                1
    4                1

.. warning::

    The two clocks are independent and are not synchronized by |eddsrecorder|.
    A consistent offset reflects the difference between the publisher clock and the sniffer clock, not a transmission
    delay.
    Only ``log_time`` is comparable across different publishers, since it comes from a single clock.

Grouping samples by their writer
================================

``writer_guid`` identifies the DataWriter outright, so separating the contributions of several publishers needs no
join and no formatting:

.. code-block:: sql

    SELECT writer_guid, COUNT(*) AS samples,
           MIN(sequence_number) AS first_seq, MAX(sequence_number) AS last_seq
      FROM Messages
     GROUP BY writer_guid;

.. code-block:: text

    writer_guid                                   samples  first_seq  last_seq
    --------------------------------------------  -------  ---------  --------
    c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3  30       1          30

The same value appears in ``Endpoints.guid``, so the topic and the kind of the writer are one join away.

.. _user_manual_querying_database_variable_length:

******************************
Reading variable length fields
******************************

Arrays and sequences live in auxiliary tables, described in :ref:`user_manual_data_types_sequences_arrays`.
They carry the same ``(writer_guid, sequence_number)`` key as the main table, so the elements of one sample are read
by joining on it and ordering by the index columns:

.. code-block:: sql

    SELECT e.index_0, e.index_1, e.value
      FROM Data_Example_Arrays_ins_ocarray e
     WHERE e.writer_guid = :guid AND e.sequence_number = :seq
     ORDER BY e.index_0, e.index_1;

.. code-block:: text

    index_0  index_1  value
    -------  -------  -----
    0        0        1
    0        1        2
    1        0        2
    1        1        3

A multidimensional array has one index column per dimension; a sequence has ``index_0`` only.
Sequence lengths vary per sample, so counting the rows of the auxiliary table gives the length each sample carried:

.. code-block:: sql

    SELECT m.sequence_number, COUNT(e.value) AS length
      FROM Messages m
      LEFT JOIN Data_Example_Sequences_selo e USING (writer_guid, sequence_number)
     GROUP BY m.writer_guid, m.sequence_number;

.. _user_manual_querying_database_exporting:

*********
Exporting
*********

The ``sqlite3`` client exports any query result to CSV, which is convenient to continue the analysis in a spreadsheet
or in a data analysis library:

.. code-block:: bash

    sqlite3 -header -csv HelloWorld-queryable.db \
        "SELECT log_time, counter, message FROM Data_Example_HelloWorld_flat ORDER BY log_time;" \
        > helloworld.csv
