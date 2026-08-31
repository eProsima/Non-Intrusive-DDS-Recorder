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
``Example HelloWorld`` is stored in the table ``Example_HelloWorld``.

To follow along, open the database with:

.. code-block:: bash

    sqlite3 HelloWorld.db

The examples below are shown with the column headers enabled, which the client turns on with
``.headers on`` and ``.mode column``.

.. _user_manual_querying_database_exploring:

**********************
Exploring the database
**********************

Listing the recorded topics
===========================

Every DDS Topic seen in the discovery traffic appears in ``_topics``, together with the number of endpoints announced
for it:

.. code-block:: sql

    SELECT t.topic_name, t.type_name,
           (SELECT COUNT(*) FROM _endpoints e
             WHERE e.topic_name = t.topic_name AND e.endpoint_type = 'DataWriter') AS writers,
           (SELECT COUNT(*) FROM _endpoints e
             WHERE e.topic_name = t.topic_name AND e.endpoint_type = 'DataReader') AS readers
    FROM _topics t;

.. code-block:: text

    topic_name          type_name   writers  readers
    ------------------  ----------  -------  -------
    Example HelloWorld  HelloWorld  1        1

Listing the tables that hold samples
====================================

The user topic tables are the ones whose name does not start with an underscore:

.. code-block:: sql

    SELECT name FROM sqlite_master
     WHERE type = 'table' AND name NOT LIKE '\_%' ESCAPE '\'
     ORDER BY name;

.. code-block:: text

    name
    ------------------
    Example_HelloWorld

Comparing this list against ``_topics`` immediately shows which topics were discovered but not recorded, that is, those
whose data type could not be resolved.

Reading the data type of a topic
================================

The IDL rendering of the type that was used to build a topic table is stored with the topic:

.. code-block:: sql

    SELECT typecode FROM _topics WHERE topic_name = 'Example HelloWorld';

.. code-block:: idl

    struct HelloWorld {
       long counter;
       string  message;
    };

.. _user_manual_querying_database_entities:

***********************
Inspecting the entities
***********************

Displaying Guids in the usual notation
======================================

Guids are stored as four separate unsigned integers.
``printf`` renders them in the hexadecimal notation that DDS tools use:

.. code-block:: sql

    SELECT printf('%08x.%08x.%08x.%08x', rtps_host_id, rtps_app_id,
                  rtps_instance_id, rtps_entity_id) AS guid,
           endpoint_type, topic_name
    FROM _endpoints
    ORDER BY topic_name, endpoint_type;

.. code-block:: text

    guid                                 endpoint_type  topic_name
    -----------------------------------  -------------  ------------------
    c0a84405.00001598.00000001.80000004  DataReader     Example HelloWorld
    c0a8010c.00001904.00000001.80000003  DataWriter     Example HelloWorld

Finding topics that need an IDL file
====================================

An endpoint announced without a :term:`TypeCode` cannot be recorded unless the type is supplied with ``-idl``.
This query lists the topics affected:

.. code-block:: sql

    SELECT DISTINCT topic_name, endpoint_type
    FROM _endpointDiscoveryMessages
    WHERE contains_typecode = 0;

An empty result, which is the case in the example, means every endpoint carried its data type definition.

.. _user_manual_querying_database_samples:

*********************
Analyzing the samples
*********************

Listing samples in capture order
================================

``message_id`` is the packet number in the capture file, so ordering by it reproduces the order in which the traffic
was observed:

.. code-block:: sql

    SELECT message_id,
           datetime(sniffer_timestamp_sec, 'unixepoch') AS captured_at,
           counter, message
    FROM Example_HelloWorld
    ORDER BY message_id
    LIMIT 4;

.. code-block:: text

    message_id  captured_at          counter  message
    ----------  -------------------  -------  ------------
    38          2013-06-18 13:08:52  0        HelloWorld 0
    45          2013-06-18 13:08:52  0        HelloWorld 0
    55          2013-06-18 13:08:56  1        HelloWorld 1
    59          2013-06-18 13:09:00  2        HelloWorld 2

For sub-second resolution, combine both halves of the sniffer timestamp:

.. code-block:: sql

    SELECT message_id,
           printf('%d.%06d', sniffer_timestamp_sec, sniffer_timestamp_usec) AS capture_ts
    FROM Example_HelloWorld
    ORDER BY message_id;

Detecting repeated samples
==========================

The same sample often appears more than once in a capture, because it was sent to several destinations or
retransmitted.
Grouping by an application-level field reveals it:

.. code-block:: sql

    SELECT counter, COUNT(*) AS occurrences,
           MIN(message_id) AS first_packet, MAX(message_id) AS last_packet
    FROM Example_HelloWorld
    GROUP BY counter
    HAVING COUNT(*) > 1
    ORDER BY counter;

.. code-block:: text

    counter  occurrences  first_packet  last_packet
    -------  -----------  ------------  -----------
    0        2            38            45

.. note::

    |eddsrecorder| records what was sent on the wire, one row per RTPS ``DATA`` submessage observed.
    A row is a *transmission* of a sample, not a distinct sample written by the application, so counting rows
    overestimates the number of writes whenever samples are sent to several destinations.

Measuring the publication period
================================

The gap between consecutive transmissions is obtained with a window function over the sniffer timestamp, expressed in
microseconds:

.. code-block:: sql

    SELECT message_id, counter,
           (sniffer_timestamp_sec * 1000000 + sniffer_timestamp_usec) -
           LAG(sniffer_timestamp_sec * 1000000 + sniffer_timestamp_usec)
               OVER (ORDER BY message_id) AS delta_usec
    FROM Example_HelloWorld
    ORDER BY message_id;

.. code-block:: text

    message_id  counter  delta_usec
    ----------  -------  ----------
    38          0
    45          0        164098
    55          1        3837054
    59          2        4001239
    62          3        4001247

The publisher writes every four seconds; the much shorter first interval is the second transmission of sample ``0``
identified above.

Comparing the source clock against the capture clock
====================================================

Each sample carries two timestamps: ``src_timestamp_*``, written by the publishing participant with its own clock, and
``sniffer_timestamp_*``, added by the sniffer.
Their difference mixes clock offset with time in flight, which makes it a practical way to spot nodes whose clocks
are not synchronized:

.. code-block:: sql

    SELECT message_id,
           (sniffer_timestamp_sec - src_timestamp_sec) * 1000
           + (sniffer_timestamp_usec / 1000 - src_timestamp_nanosec / 1000000) AS skew_ms
    FROM Example_HelloWorld
    ORDER BY message_id
    LIMIT 4;

.. code-block:: text

    message_id  skew_ms
    ----------  -------
    38          -531
    45          -367
    55          -529
    59          -537

.. warning::

    The two clocks are independent and are not synchronized by |eddsrecorder|.
    A consistent offset such as the one above reflects the difference between the publisher clock and the sniffer
    clock, not a transmission delay.
    Only ``sniffer_timestamp_*`` is comparable across different publishers, since it comes from a single clock.

Grouping samples by their source
================================

Samples record the :term:`GuidPrefix` of the participant that sent them, which is enough to separate the contributions
of several publishers:

.. code-block:: sql

    SELECT printf('%08x.%08x.%08x', src_rtps_host_id, src_rtps_app_id,
                  src_rtps_instance_id) AS participant,
           COUNT(*) AS samples,
           MIN(message_id) AS first_packet, MAX(message_id) AS last_packet
    FROM Example_HelloWorld
    GROUP BY 1;

.. code-block:: text

    participant                 samples  first_packet  last_packet
    --------------------------  -------  ------------  -----------
    c0a8010c.00001904.00000001  31       38            143

Resolving the writer of a sample
================================

Topic tables store the participant prefix but not the entity id of the writer, so the DataWriter is recovered by
joining against ``_endpoints`` on the prefix and the topic:

.. code-block:: sql

    SELECT s.message_id, s.counter,
           printf('%08x.%08x.%08x.%08x', e.rtps_host_id, e.rtps_app_id,
                  e.rtps_instance_id, e.rtps_entity_id) AS writer_guid
    FROM Example_HelloWorld s
    JOIN _endpoints e
      ON  e.rtps_host_id     = s.src_rtps_host_id
      AND e.rtps_app_id      = s.src_rtps_app_id
      AND e.rtps_instance_id = s.src_rtps_instance_id
      AND e.topic_name       = 'Example HelloWorld'
      AND e.endpoint_type    = 'DataWriter'
    ORDER BY s.message_id
    LIMIT 3;

.. code-block:: text

    message_id  counter  writer_guid
    ----------  -------  -----------------------------------
    38          0        c0a8010c.00001904.00000001.80000003
    45          0        c0a8010c.00001904.00000001.80000003
    55          1        c0a8010c.00001904.00000001.80000003

.. warning::

    This join is only unambiguous when the participant owns a single DataWriter on the topic.
    If it owns several, the join returns one row per writer and the sample cannot be attributed to a particular one.

.. _user_manual_querying_database_variable_length:

******************************
Reading variable length fields
******************************

Arrays and sequences live in auxiliary tables, described in :ref:`user_manual_data_types_sequences_arrays`.
For a topic ``Foo`` with a field ``myArray``, the elements of one sample are read by joining on the ``myArray_id``
column and ordering by the index:

.. code-block:: sql

    SELECT Foo_myArray.index_0, Foo_myArray.value
    FROM Foo
    INNER JOIN Foo_myArray ON Foo.myArray_id = Foo_myArray.myArray_id
    WHERE Foo.message_id = <a_Valid_Id>
    ORDER BY Foo_myArray.index_0;

For a multidimensional array, order by every index column in turn, ``index_0``, ``index_1``, and so on.
Sequence lengths vary per sample, so counting the rows of the auxiliary table gives the length that each sample
carried:

.. code-block:: sql

    SELECT Foo.message_id, COUNT(Foo_mySeq.value) AS sequence_length
    FROM Foo
    LEFT JOIN Foo_mySeq ON Foo.mySeq_id = Foo_mySeq.mySeq_id
    GROUP BY Foo.message_id;

.. _user_manual_querying_database_exporting:

*********
Exporting
*********

The ``sqlite3`` client exports any query result to CSV, which is convenient to continue the analysis in a spreadsheet
or in a data analysis library:

.. code-block:: bash

    sqlite3 -header -csv HelloWorld.db \
        "SELECT message_id, counter, message FROM Example_HelloWorld ORDER BY message_id;" \
        > helloworld.csv
