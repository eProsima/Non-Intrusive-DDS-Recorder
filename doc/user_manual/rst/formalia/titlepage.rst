#################################################
eProsima Non-Intrusive DDS Recorder Documentation
#################################################

.. image:: /rst/figures/eprosima_logo.svg
  :height: 100px
  :width: 100px
  :align: left
  :alt: eProsima
  :target: http://www.eprosima.com/

*eProsima Non-Intrusive DDS Recorder* is a tool that records all the DDS traffic in a network using a non-intrusive
mechanism, allowing a user to test, analyze or log a DDS distributed system without adding any new DDS participant or
service.
Because no entity is added to the network, the recorded data reflects the real behavior and timing of the system under
study.

*eProsima Non-Intrusive DDS Recorder* sniffs the DDS wire protocol (RTPS) instead of subscribing to the topics of
interest.
It dissects the protocol, builds a complete database of all the DDS entities (Participants, Publishers, Subscribers and
Topics), the data types and all the exchanged messages, and stores the result in a `SQLite <https://www.sqlite.org/>`_
database that can be inspected with any standard SQL client.

##################
Commercial support
##################

Looking for commercial support? Write us to info@eprosima.com

Find more about us at `eProsima's webpage <https://eprosima.com/>`__.

########
Overview
########

*eProsima Non-Intrusive DDS Recorder* does not record raw network data: it builds a message table for each DDS Topic,
with the same fields as the corresponding DDS Topic data type.
The application provides the following features:

* **Non-intrusive capture**.
  Traffic is taken from a packet capture (:term:`PCAP`) file produced by a network sniffer, so no DDS entity is created
  and the observed system is not modified in any way.
  In order to capture all the traffic in a network, the switch debug port should be sniffed; otherwise only the traffic
  directed to the node where the sniffer runs is obtained.

* **Automatic entity discovery**.
  DDS uses an automatic discovery process to announce all the DDS entities in a network.
  *eProsima Non-Intrusive DDS Recorder* analyzes the discovery traffic to learn which topics exist and which
  DataWriters and DataReaders serve them, so every sample it captures can be attributed to a topic.
  Supply an :term:`IDL` file with the type definitions to have the samples deserialized into columns as well.

* **Human readable output**.
  The RTPS messages are translated into a human readable format and stored in a :term:`SQLite` database.
  Both the discovery information and the user data are available as regular SQL tables, so the recorded session can be
  queried, filtered and post-processed with any tool able to read a SQLite file.

.. note::

    This release requires an external sniffer, such as *Wireshark*, to save the network traffic into a standard packet
    capture file.
    Future releases will include a built-in sniffer to process the network packets in real time.

A recording session therefore has three steps: capture the traffic with a sniffer, run the application on the
resulting file, and query the database it produces.

.. code-block:: bash

    # 1. Capture the DDS traffic, keeping whole packets
    sudo tcpdump -i eth0 -s 0 -w capture.pcap udp

    # 2. Translate the capture into a SQLite database
    DDSRecorder -db session.db capture.pcap

    # 3. Query the result
    sqlite3 session.db "SELECT name, type FROM Topics;"

#################################
Contributing to the documentation
#################################

*Non-Intrusive DDS Recorder Documentation* is an open source project, and as such all contributions, both in the form of
feedback and content generation, are most welcomed.
To make such contributions, please refer to the
`Contribution Guidelines <https://github.com/eProsima/all-docs/blob/master/CONTRIBUTING.md>`_ hosted in our GitHub
repository.

##############################
Structure of the documentation
##############################

This documentation is organized into the sections below.

* :ref:`Installation Manual <installation_manual_requirements>`: requirements and installation instructions for
  Windows and Linux.
* :ref:`User Manual <user_manual_introduction>`: how the tool works, when to use it, how to obtain a usable capture,
  the command line reference, the structure of the generated database, the supported data types, a collection of SQL
  recipes to analyze a recorded session, and the limitations of the current release.
* :ref:`Release Notes <notes>`: supported platforms, databases, DDS implementations and capture formats.
* :ref:`Glossary <glossary>`: the nomenclature used throughout this documentation.

New users are advised to start with :ref:`user_manual_introduction`, which explains what the application records and
links to the rest of the User Manual in reading order.
