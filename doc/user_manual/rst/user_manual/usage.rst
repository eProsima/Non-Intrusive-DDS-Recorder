.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_usage:

#####
Usage
#####

|eddsrecorder| is a command line application that reads a capture file and writes a :term:`SQLite` database:

.. code-block:: bash

    DDSRecorder <pcapFile> [-db <database>] [-idl <file>] [-queryable] [-help]

.. _user_manual_usage_application_arguments:

***********************
Command-Line Parameters
***********************

.. list-table::
    :header-rows: 1
    :widths: 18 12 12 12 46

    *   - Command
        - Option
        - Value
        - Default
        - Description

    *   - Capture File
        - ``<pcapFile>``
        - String
        -
        - Path of the capture file to analyze, in |br|
          :term:`PCAP` format. |br|
          The argument has no flag: any token that |br|
          is not recognized as an option is taken |br|
          as the capture file name.

    *   - Database
        - ``-db``
        - String
        - ``dump.db``
        - Path of the SQLite file that will hold |br|
          the translated RTPS messages.

    *   - IDL File
        - ``-idl``
        - String
        -
        - IDL file describing the data types used |br|
          in the captured system. |br|
          It is the only source of data types: |br|
          the RTPS traffic carries no type |br|
          description |eddsrecorder| reads. |br|
          Without it a capture is still recorded, |br|
          it simply carries no type description |br|
          and gets no per-topic table. |br|
          See |br|
          :ref:`user_manual_usage_idl_naming_policy`.

    *   - Queryable schema
        - ``-queryable``
        -
        -
        - Also store each sample in a table of |br|
          its own DDS Topic, with one column |br|
          per data type member. |br|
          This *adds to* the |br|
          *DDS Record & Replay* tables rather |br|
          than replacing them, so a recording |br|
          made with it can still be replayed. |br|
          Needs ``-idl`` to know the data types. |br|
          See |br|
          :ref:`user_manual_database_structure`.

    *   - Help
        - ``-help``
        -
        -
        - Print the usage information and exit.

.. note::

    The *DDS Record & Replay* and *DDS Monitor* schema is always written, whatever the arguments.
    It stores every sample as its raw :term:`CDR` payload and needs no data type at all, which is why a capture is
    recorded in full even when no IDL file describes it.
    ``-queryable`` adds tables beside it: one per DDS Topic with one column per data type member, plus the packet
    level tables the capture reveals and the schema has no column for.
    :ref:`user_manual_monitor_schema` describes the former, and
    :ref:`user_manual_database_structure` describes what ``-queryable`` adds.

.. warning::

    |eddsrecorder| does not append to an existing database.
    When the file passed with ``-db`` already contains tables written by a previous run, those tables are dropped or
    emptied before the new capture is processed.
    Use a different file name for each capture you want to keep.

.. _user_manual_usage_example:

****************
Example of usage
****************

This section walks through the example distributed with the application, located at:

.. code-block:: text

    [Recorder Install dir]/examples/HelloWorld

The folder contains three files: the IDL file describing the data type, a sample PCAP file with the sniffed traffic of
a simple DDS publisher and subscriber, and the SQLite database that results from processing it.
The data type is:

.. code-block:: idl

    struct HelloWorld {
        long counter;
        string message;
    };

The publisher writes the samples on a topic named ``Example HelloWorld``.

Generating the applications and sniffing some network packets
=============================================================

Most DDS implementations provide an IDL compiler that generates the type support for a user data type together with an
example publisher-subscriber application.
In the case of |efastdds|, that tool is ``Fast DDS-Gen``.
Use it to generate a simple publisher/subscriber pair, run it, and record the traffic with a network sniffer as
described in :ref:`user_manual_capturing_traffic`.

.. note::

    This step can be skipped, as a sample PCAP file is provided with the application.

Generating the SQLite database
==============================

Run |eddsrecorder| on the capture to produce the database.
Make sure you have permission to create files in the working directory:

.. code-block:: bash

    DDSRecorder -db HelloWorld.db HelloWorld.pcap

The application reports its progress and the number of RTPS packets it recognized:

.. code-block:: text

    Processing file...
    Number of processed RTPS packets: 147

A count of zero means that no RTPS traffic was found in the capture.
:ref:`user_manual_limitations_troubleshooting` lists the usual causes.

.. note::

    Do not rely on the process exit status to detect failures: |eddsrecorder| returns the same non-zero status on
    success and on error.
    Check the printed packet count and the ``ERROR<...>`` lines on the console instead.

Understanding the SQLite database
=================================

The recording above used no ``-idl`` file, so it holds the samples but no description of their data type.
Record it again with the IDL that ships beside the capture to get both:

.. code-block:: bash

    DDSRecorder -db HelloWorld.db -idl HelloWorld.idl HelloWorld.pcap

The database now contains the six tables of the *DDS Record & Replay* schema:

.. code-block:: text

    Messages  MessagesPartitions  Partitions  Topics  TopicsPartitions  Types

:ref:`user_manual_monitor_schema` describes each of them.
It is possible to browse the database through numerous graphical interfaces; every result shown here can also be
obtained with the ``sqlite3`` command line client.

Topics and Types
----------------

``Topics`` holds the DDS Topic and the name of its data type, and ``Types`` holds the type itself, rendered as IDL
from the file given with ``-idl``:

.. code-block:: sql

    SELECT name, type FROM Topics;
    SELECT idl FROM Types;

.. code-block:: text

    Example HelloWorld|HelloWorld

    @extensibility(APPENDABLE)
    struct HelloWorld
    {
        long counter;
        string message;
    };

Without ``-idl`` the ``Types`` row is still written, with an empty ``idl`` column.
The ``information`` and ``object`` columns stay empty in every case: they are meant for an XTypes ``TypeIdentifier``
and ``TypeObject``, and |eddsrecorder| reads no XTypes type information from the wire.

Messages
--------

``Messages`` holds one row per sample, keyed on the writer and the sequence number, with the payload kept as the raw
:term:`CDR` it traveled as:

.. code-block:: sql

    SELECT sequence_number, log_time, data_cdr_size FROM Messages ORDER BY sequence_number LIMIT 3;

.. code-block:: text

    1|2013-06-18 13:08:52.160848000|28
    2|2013-06-18 13:08:56.162000000|28
    3|2013-06-18 13:09:00.163239000|28

``log_time`` is when the sniffer saw the packet and ``publish_time`` is the source timestamp the writer put in it.

Adding the queryable tables
===========================

``-queryable`` keeps everything above and adds to it:

.. code-block:: bash

    DDSRecorder -db HelloWorld-queryable.db -queryable -idl HelloWorld.idl HelloWorld.pcap

Four more tables appear, plus one table and one view for the topic itself:

.. code-block:: text

    DataTables  DiscoveryMessages  Endpoints  MessagesCapture
    Data_Example_HelloWorld  Data_Example_HelloWorld_flat

Endpoints and DiscoveryMessages
-------------------------------

|eddsrecorder| finds two endpoint discovery messages, one from the publisher and one from the subscriber application.
``Endpoints`` holds the endpoints they announced, and ``DiscoveryMessages`` holds the packets that announced them:

.. code-block:: sql

    SELECT guid, kind FROM Endpoints;
    SELECT packet_id, ip_src, ip_dst, kind FROM DiscoveryMessages;

.. code-block:: text

    c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3|DataWriter
    c0.a8.44.05.00.00.15.98.00.00.00.01|80.0.0.4|DataReader

    23|192.168.1.12|239.255.0.1|DataWriter
    29|192.168.1.26|192.168.1.12|DataReader

``Endpoints.guid`` is spelled exactly as ``Messages.writer_guid``, so the two join without conversion.

MessagesCapture
---------------

``Messages`` describes the recording as a DDS application would see it, so it says nothing about which packet carried
a sample or between which addresses.
``MessagesCapture`` holds that, one row per packet:

.. code-block:: sql

    SELECT COUNT(*) FROM Messages;
    SELECT COUNT(*) FROM MessagesCapture;

.. code-block:: text

    30
    31

The counts differ because one sample traveled twice.
``Messages`` is keyed on ``(writer_guid, sequence_number)`` and holds it once; ``MessagesCapture`` keeps both
transmissions, so the repetition the capture witnessed is not lost:

.. code-block:: sql

    SELECT writer_guid, sequence_number, COUNT(*) FROM MessagesCapture
        GROUP BY 1, 2 HAVING COUNT(*) > 1;

.. code-block:: text

    c0.a8.01.0c.00.00.19.04.00.00.00.01|80.0.0.3|1|2

The topic table
---------------

``Data_Example_HelloWorld`` holds the deserialized samples, one column per member of the data type:

.. code-block:: text

    writer_guid  sequence_number  counter  message

The first two columns are the key back into ``Messages``; ``counter`` and ``message`` are the fields of the
``HelloWorld`` data type.
Note that the table is named ``Data_Example_HelloWorld`` while the topic is named ``Example HelloWorld``: the blank
space is not valid in a SQL identifier and is replaced by an underscore.
``DataTables`` records the mapping, so it is never necessary to reproduce that substitution by hand:

.. code-block:: sql

    SELECT topic, member_path, table_name FROM DataTables;

.. code-block:: text

    Example HelloWorld||Data_Example_HelloWorld

Reading a sample beside its timestamps means joining ``Messages``.
The ``_flat`` view does that join once, and reads like a single table:

.. code-block:: sql

    SELECT log_time, counter, message FROM Data_Example_HelloWorld_flat ORDER BY log_time LIMIT 4;

.. code-block:: text

    2013-06-18 13:08:52.160848000|0|HelloWorld 0
    2013-06-18 13:08:56.162000000|1|HelloWorld 1
    2013-06-18 13:09:00.163239000|2|HelloWorld 2
    2013-06-18 13:09:04.164486000|3|HelloWorld 3

:ref:`user_manual_querying_database` shows more of what can be asked of the schema.

.. _user_manual_usage_idl_naming_policy:

********************************
A note on IDL file naming policy
********************************

The RTPS traffic carries no data type description that |eddsrecorder| reads, so an IDL file given through the
``-idl`` argument is the only way to describe the types of a captured system.
Without one the capture is still recorded in full, as :term:`CDR`, but ``Types.idl`` stays empty and ``-queryable``
produces no topic table.
Two rules apply to that file:

* **The struct name must match the type name announced on the wire.**
  |eddsrecorder| looks up the type by the ``dataType`` name found in the discovery messages.
  For example, if a topic is named ``SimpleDataTopic`` and its type is ``SimpleDataType``, the structure defining it in
  the IDL must be named ``SimpleDataType``.

* **The file must declare every type you want described.**
  It is parsed once, as a whole, and every structure, union, enumeration and alias in it is kept.
  A topic whose type is not among them is recorded without a description, which is not an error.

Member names are emitted as quoted SQL identifiers, so a member named after an SQLite keyword, such as ``index`` or
``order``, needs no renaming.

If the file cannot be parsed, |eddsrecorder| prints ``Error parsing the IDL file`` and stops without processing the
capture.
