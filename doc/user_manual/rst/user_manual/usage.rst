.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_usage:

#####
Usage
#####

|eddsrecorder| is a user application executed from the command line with the following syntax:

.. code-block:: bash

    DDSRecorder <pcapFile> [-db <database>] [-tcMaxSize <size>] [-idl <file>] [-help]

.. _user_manual_usage_application_arguments:

***********************
Command-Line Parameters
***********************

The |eddsrecorder| application supports the following input arguments:

.. list-table::
    :header-rows: 1

    *   - Command
        - Description
        - Option
        - Possible Values
        - Default Value

    *   - Capture File
        - Name of the file that the |br|
          application will analyze. |br|
          This file must be in |br|
          PCAP format.
        - ``<pcapFile>``
        - String
        -

    *   - Database
        - Name of the SQLite file |br|
          that will be created and |br|
          used to store the |br|
          translated RTPS messages.
        - ``-db``
        - String
        - ``dump.db``

    *   - TypeCode Max Size
        - TypeCode maximum allowed |br|
          size.
        - ``-tcMaxSize``
        - Unsigned Integer
        - ``2048``

    *   - IDL File
        - IDL file containing the |br|
          data types used in the |br|
          captured system. |br|
          Only needed if their |br|
          TypeCodes are not sent |br|
          in the discovery phase.
        - ``-idl``
        - String
        -

    *   - Help
        - Print help information.
        - ``-help``
        -
        -

.. _user_manual_usage_example:

****************
Example of usage
****************

This section provides a step-by-step use example of the tool through an example located at:

.. code-block:: text

    [Recorder Install dir]/examples/HelloWorld

The folder contains the IDL file used for the data type, a sample PCAP file containing the sniffed traffic from a
simple DDS Publisher and Subscriber application, and the generated SQLite database.
The data type is described as follows:

.. code-block:: idl

    struct HelloWorld {
        long counter;
        string message;
    };

It is possible to browse the SQLite database through numerous graphical interfaces.
In this section the `SQLiteman <http://sqliteman.com/>`_ GUI tool is used.

Generating the applications and sniffing some network packets
=============================================================

Most DDS implementations provide an IDL compiler to generate type support for user data types and an example
publisher-subscriber application.
In the case of |efastdds|, this application is ``FastDDSGen``.
Use it to generate a simple publisher/subscriber application, run it and save some network traffic using a network
sniffer such as *Wireshark*, saving the results as a PCAP file.

.. note::

    This step can be skipped, as a sample PCAP file is provided with the application.

Generating the SQLite database
==============================

|eddsrecorder| is then used to generate the SQLite database that stores the previously captured RTPS messages in a
human readable format.
To create the database, run the following command after making sure you have appropriate permissions to create files in
your working folder:

.. code-block:: bash

    DDSRecorder -db HelloWorld.db HelloWorld.pcap

Understanding the SQLite database
=================================

For this example, |eddsrecorder| creates four tables in the generated SQLite database:

.. figure:: /rst/figures/helloworld_db_tables.png
    :align: center

    Tables created for the *HelloWorld* example

Refer to :ref:`user_manual_database_structure` for a detailed explanation of the whole schema.

_endpointDiscoveryMessages table
--------------------------------

|eddsrecorder| finds two endpoint discovery RTPS messages from the publisher and subscriber applications.
The ``_endpointDiscoveryMessages`` table shows these entries, corresponding to a DDS :term:`DataWriter` and a DDS
:term:`DataReader`:

.. figure:: /rst/figures/helloworld_endpoint_discovery_messages.png
    :align: center

    Endpoint discovery messages found in the capture

|eddsrecorder| extracts the information about endpoints and topics from the discovery messages, thus creating the two
following tables.

_endpoints table
----------------

Table ``_endpoints`` shows the two DDS endpoints detected in the discovery traffic, a DataReader and a DataWriter.

.. figure:: /rst/figures/helloworld_endpoints.png
    :align: center

    Endpoints detected in the discovery traffic

_topics table
-------------

Table ``_topics`` shows a human readable IDL representation of the TypeCode of the present topic.

.. figure:: /rst/figures/helloworld_topics.png
    :align: center

    Topics detected in the discovery traffic

example_helloworld table
------------------------

This table contains the data and metadata related to the samples that have been captured during the session.

.. figure:: /rst/figures/helloworld_topic_table.png
    :align: center

    Samples recorded for the *HelloWorld* topic

.. _user_manual_usage_idl_naming_policy:

********************************
A note on IDL file naming policy
********************************

Some implementations, like *RTI DDS*, send information about the data type structures as part of the discovery process.
This is not considered the norm, therefore if you use |ddsrecord| with a library that does not support this feature it
is mandatory to provide an IDL file with the type definitions through the ``-idl`` argument.
Two points must be taken into account when providing this file:

* The name of the struct must be equal to the name of the ``dataType`` field used in the RTPS network.
  For example, if a topic has a name ``SimpleDataTopic`` and type ``SimpleDataType``, the name of the structure that
  defines it in the IDL must be ``SimpleDataType``.

* None of the members of a structure in the IDL can have names that may come into conflict with SQLite reserved words.
  |ddsrecord| has built-in protection against this by, for instance, replacing fields with the name ``index`` with
  ``index_``.
