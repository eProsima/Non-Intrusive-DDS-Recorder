.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_usage:

#####
Usage
#####

|eddsrecorder| is a command line application that reads a capture file and writes a :term:`SQLite` database:

.. code-block:: bash

    DDSRecorder <pcapFile> [-db <database>] [-tcMaxSize <size>] [-idl <file>] [-help]

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

    *   - TypeCode Max Size
        - ``-tcMaxSize``
        - Integer
        - ``2048``
        - Maximum serialized size, in bytes, |br|
          accepted for a :term:`TypeCode` found |br|
          in the discovery traffic. |br|
          Accepted and validated, but it has |br|
          **no effect** in this release: |br|
          TypeCodes are deserialized |br|
          regardless of the value given.

    *   - IDL File
        - ``-idl``
        - String
        -
        - IDL file describing the data types used |br|
          in the captured system. |br|
          Only needed when their TypeCodes are |br|
          not sent during the discovery phase. |br|
          See |br|
          :ref:`user_manual_usage_idl_naming_policy`.

    *   - Help
        - ``-help``
        -
        -
        - Print the usage information and exit.

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

For this example, |eddsrecorder| creates four tables in the generated SQLite database:

.. figure:: /rst/figures/helloworld_db_tables.png
    :align: center

    Tables created for the *HelloWorld* example

Three of them start with an underscore and hold the discovery information; the fourth one holds the recorded samples.
Refer to :ref:`user_manual_database_structure` for a detailed explanation of the whole schema.

It is possible to browse the database through numerous graphical interfaces; the figures in this section use the
`SQLiteman <http://sqliteman.com/>`_ GUI tool.
Every result shown here can also be obtained with the ``sqlite3`` command line client.

_endpointDiscoveryMessages table
--------------------------------

|eddsrecorder| finds two endpoint discovery RTPS messages, one from the publisher and one from the subscriber
application.
The ``_endpointDiscoveryMessages`` table shows these entries, corresponding to a DDS :term:`DataWriter` and a DDS
:term:`DataReader`:

.. figure:: /rst/figures/helloworld_endpoint_discovery_messages.png
    :align: center

    Endpoint discovery messages found in the capture

The ``contains_typecode`` column is ``1`` in both rows, which means the discovery traffic carried the data type
definition and no ``-idl`` file was needed.

|eddsrecorder| extracts the information about endpoints and topics from these discovery messages, thus creating the two
following tables.

_endpoints table
----------------

Table ``_endpoints`` shows the two DDS endpoints detected in the discovery traffic, a DataReader and a DataWriter.

.. figure:: /rst/figures/helloworld_endpoints.png
    :align: center

    Endpoints detected in the discovery traffic

_topics table
-------------

Table ``_topics`` shows a human readable IDL representation of the TypeCode of the present topic:

.. figure:: /rst/figures/helloworld_topics.png
    :align: center

    Topics detected in the discovery traffic

.. code-block:: idl

    struct HelloWorld {
       long counter;
       string  message;
    };

This rendering is what |eddsrecorder| used to lay out the columns of the topic table below, which makes it the first
place to look when a column is missing or has an unexpected type.

Example_HelloWorld table
------------------------

This table contains the data and the protocol metadata of every sample captured during the session.

.. figure:: /rst/figures/helloworld_topic_table.png
    :align: center

    Samples recorded for the *HelloWorld* topic

Note that the table is named ``Example_HelloWorld`` while the topic is named ``Example HelloWorld``: the blank space is
not valid in a SQL identifier and is replaced by an underscore.
:ref:`user_manual_database_structure_table_names` describes the complete set of substitutions.

The two rightmost columns, ``counter`` and ``message``, are the fields of the ``HelloWorld`` data type.
All the columns to their left are the protocol metadata that |eddsrecorder| adds to every sample.
For instance, the recorded samples can be listed in capture order with:

.. code-block:: sql

    SELECT message_id, counter, message FROM Example_HelloWorld ORDER BY message_id;

.. code-block:: text

    38|0|HelloWorld 0
    45|0|HelloWorld 0
    55|1|HelloWorld 1
    59|2|HelloWorld 2

The first two rows carry the same ``counter``: the sample was sent twice.
:ref:`user_manual_querying_database` shows how to detect and filter such repetitions.

.. _user_manual_usage_idl_naming_policy:

********************************
A note on IDL file naming policy
********************************

Not every DDS implementation sends the definition of its data types as part of the discovery process.
When |eddsrecorder| is used with a library that does not, an IDL file with the type definitions must be provided
through the ``-idl`` argument.
Three rules apply to that file:

* **The struct name must match the type name announced on the wire.**
  |eddsrecorder| looks up the type by the ``dataType`` name found in the discovery messages.
  For example, if a topic is named ``SimpleDataTopic`` and its type is ``SimpleDataType``, the structure defining it in
  the IDL must be named ``SimpleDataType``.

* **Member names must be valid, unquoted SQL identifiers.**
  Member names are used verbatim as column names, so a member whose name is an SQLite keyword, such as ``index``,
  ``order`` or ``group``, makes the creation of the topic table fail and the topic is not recorded.
  Rename the member in the IDL file supplied to |eddsrecorder| when this happens; the name only has to match on the
  wire at the type level, not at the member level.

* **Member names must not collide with the protocol metadata columns.**
  |eddsrecorder| adds its own columns in front of every topic table, so avoid members named ``message_id``, ``ip_src``,
  ``ip_dst`` or any of the other names listed in
  :ref:`user_manual_database_structure_metadata`.

If the file cannot be parsed, |eddsrecorder| prints ``Error parsing the IDL file`` and stops without processing the
capture.
