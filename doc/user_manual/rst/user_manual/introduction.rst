.. include:: ../exports/alias.include

.. _user_manual_introduction:

############
Introduction
############

|eddsrecorder| turns the RTPS traffic of a DDS network into an :term:`SQLite` database you can query with plain SQL.
Because it works from a packet capture and never joins the DDS network, it lets you test, analyze or log a distributed
system without adding a single DDS entity to it, so the recorded data reflects the real behavior and timing of the
system under study.
:ref:`user_manual_use_cases` describes the situations in which that property is worth the trade-offs it implies.

************
How it works
************

|eddsrecorder| never subscribes to a topic.
Instead, it reads a packet capture (:term:`PCAP`) file produced by an external sniffer such as
`Wireshark <https://www.wireshark.org/>`_ and dissects the DDS wire protocol, :term:`RTPS`, found inside it.

The application works in four stages:

#. **Packet extraction.**
   Every Ethernet frame in the capture is examined, IPv4 fragments are reassembled, and the UDP payloads that begin
   with the ``RTPS`` magic word are handed over to the protocol dissector.

#. **Entity discovery.**
   The :term:`SEDP` messages that DDS uses to announce its endpoints are decoded to learn which
   :term:`DataWriter`\ s and :term:`DataReader`\ s exist, which :term:`Topic` each of them serves, and which data type
   that topic carries.

#. **Type resolution.**
   The data type schema is taken from the :term:`TypeCode` embedded in the discovery messages.
   When the DDS implementation under study does not publish that information, an :term:`IDL` file supplied with the
   ``-idl`` argument is used instead.

#. **Sample storage.**
   With the schema known, |eddsrecorder| creates one SQL table per topic and decodes every user sample in the capture
   into a row of that table.

.. _user_manual_introduction_what_you_get:

************
What you get
************

|eddsrecorder| does not store raw network data.
By default it stores every sample as the raw :term:`CDR` payload that was sent on the wire, in the same schema
*eProsima DDS Monitor* reads, alongside the topics and data types found in the capture.
Nothing is decoded, so a topic is recorded even when its data type was never announced:

.. code-block:: sql

    SELECT topic, type, COUNT(*) FROM Messages GROUP BY topic, type;

Passing ``-queryable`` gives the other shape instead: a table per DDS Topic whose columns are the members of its data
type, next to the protocol metadata of each sample, so the recorded values can be read with plain SQL:

.. code-block:: sql

    SELECT counter, message FROM Example_HelloWorld ORDER BY message_id;

That one also records the discovery information as tables of its own: the topics found in the capture together with a
human readable rendering of their data types, the endpoints that were announced, and the raw endpoint discovery
messages.
:ref:`user_manual_monitor_schema` and :ref:`user_manual_database_structure` describe the two schemas, and
:ref:`user_manual_querying_database` collects ready-to-use queries over the queryable one.

.. note::

    This release requires an external sniffer to save the network traffic into a standard packet capture file.
    Future releases will include a built-in sniffer to process the network packets in real time.

*****************
Before you record
*****************

Two conditions decide whether a capture can be recorded at all, and both are set before |eddsrecorder| runs:

* **The capture must contain the traffic you care about.**
  A sniffer running on an ordinary node only sees the traffic addressed to that node.
  To observe a whole DDS network you must sniff a mirror port of the switch, also known as the
  :term:`switch debug port`.

* **The capture must contain whole packets.**
  |eddsrecorder| discards truncated packets, so the sniffer must be configured with an unlimited snapshot length.

:ref:`user_manual_capturing_traffic` explains how to satisfy both, and
:ref:`user_manual_limitations` lists what the current release can and cannot record.

****************
Where to go next
****************

* :ref:`user_manual_use_cases` — when non-intrusive recording is the right approach.
* :ref:`user_manual_capturing_traffic` — obtain a capture that |eddsrecorder| can process.
* :ref:`user_manual_usage` — command line reference and a complete worked example.
* :ref:`user_manual_monitor_schema` — the default schema, compatible with *DDS Record & Replay*.
* :ref:`user_manual_database_structure` — the ``-queryable`` schema, a table per DDS Topic.
* :ref:`user_manual_data_types` — how each IDL construct is mapped to SQL under ``-queryable``.
* :ref:`user_manual_querying_database` — SQL recipes to analyze a ``-queryable`` recording.
* :ref:`user_manual_limitations` — supported scenarios and troubleshooting.
