.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_limitations:

###############################
Limitations and troubleshooting
###############################

|eddsrecorder| reconstructs a DDS session from the bytes that were sent on the wire.
Everything that never reached the capture point, or that the dissector does not decode, is simply absent from the
resulting database.
This section states what the current release records, and maps the symptoms of an incomplete recording to their
causes.

.. _user_manual_limitations_scope:

****************
What is recorded
****************

Network layers
==============

.. list-table::
    :header-rows: 1
    :widths: 24 38 38

    *   - Layer
        - Recorded
        - Not recorded

    *   - Link
        - Ethernet II frames, and the |br|
          Windows Null/Loopback |br|
          encapsulation.
        - Any other link layer, |br|
          including VLAN tagged |br|
          frames.

    *   - Network
        - IPv4, including fragmented |br|
          datagrams, which are |br|
          reassembled.
        - IPv6.

    *   - Transport
        - UDP.
        - TCP, and the RTPS/TCP |br|
          transport built on it. |br|
          Shared memory transports |br|
          never reach the network.

    *   - RTPS
        - The ``INFO_TS``, ``INFO_DST`` |br|
          and ``DATA`` submessages.
        - ``DATA_FRAG``, and therefore |br|
          any sample large enough to |br|
          be fragmented by RTPS. |br|
          ``HEARTBEAT``, ``ACKNACK`` |br|
          and ``GAP`` are ignored, so |br|
          the reliability protocol is |br|
          not reconstructed.

DDS entities
============

|eddsrecorder| tracks DDS entities at the endpoint level.
The :term:`SEDP` announcements of DataWriters and DataReaders are decoded and stored, while the :term:`SPDP`
participant announcements are skipped: a participant is only visible through the :term:`GuidPrefix` of its endpoints.

QoS policies carried in the discovery messages are not recorded either.
Only the topic name, the type name and the :term:`TypeCode` are extracted from each announcement.

.. note::

    The ``-tcMaxSize`` argument is accepted for compatibility but has no effect in this release.
    TypeCodes found in the discovery traffic are deserialized regardless of the value given.

Data types
==========

Type resolution depends on the DDS implementation including the TypeCode of the topic in its endpoint announcements.
Implementations that do not are supported through the ``-idl`` argument, described in
:ref:`user_manual_usage_idl_naming_policy`.

The mapping of IDL constructs to SQL is described in :ref:`user_manual_data_types`.
In summary, the current release does not record:

* The ``long double``, ``wchar`` and ``wstring`` basic types.
* Sequences and arrays whose elements are user types.
* Sequences and arrays of ``string``.

Security
========

The dissector reads the RTPS submessages directly from the capture.
Traffic protected with DDS Security is encrypted on the wire and cannot be decoded.

.. _user_manual_limitations_troubleshooting:

***************
Troubleshooting
***************

The database is empty and no RTPS packets were found
====================================================

|eddsrecorder| prints ``Number of processed RTPS packets: 0``.

* The capture contains no RTPS traffic at all.
  Confirm it with the ``rtps`` display filter in Wireshark, as described in
  :ref:`user_manual_capturing_traffic_checking`.
* The traffic uses a transport that is not dissected, such as RTPS over TCP or over IPv6.
* The capture was taken on an interface that does not see the DDS traffic.
  See :ref:`user_manual_capturing_traffic_where`.

Far fewer packets than expected, with capture length errors
===========================================================

The console shows repeated errors of the form:

.. code-block:: text

    ERROR<pcapReader::processPacket>: Packet with different capture length than off wire length

The capture was taken with a limited snapshot length and its packets are truncated.
|eddsrecorder| discards each truncated packet, so a database recorded from such a capture typically ends up with the
discovery tables partially populated and no topic table at all.
Retake the capture with an unlimited snapshot length, as described in :ref:`user_manual_capturing_traffic`.
A capture that has already been truncated cannot be repaired.

The discovery tables are populated but a topic has no table
===========================================================

The topic appears in ``_topics`` and ``_endpoints``, yet no table holds its samples.

* **The data type could not be resolved.**
  Check the ``contains_typecode`` column of ``_endpointDiscoveryMessages`` for that topic; the query in
  :ref:`user_manual_querying_database_entities` lists the affected topics.
  If it is ``0``, supply the type with ``-idl``.
* **The data type uses an unsupported construct.**
  The console reports the unrecognized kind.
  See :ref:`user_manual_data_types_unsupported`.
* **A member name is not a valid SQL column name.**
  Member names are used verbatim as column names, so a member named after an SQLite keyword prevents the table from
  being created.
  See :ref:`user_manual_usage_idl_naming_policy`.
* **Two topic names collapsed onto the same table name.**
  See :ref:`user_manual_database_structure_table_names`.
* **No sample was captured.**
  Discovery is largely multicast while user samples are often unicast, so a capture point may see the announcements
  of a topic without seeing its data.

The topic table exists but some samples are missing
===================================================

* Samples large enough to be fragmented by RTPS travel in ``DATA_FRAG`` submessages, which are not processed.
* The capture point did not see the transmission, for instance because the sample was sent unicast to a reader on
  another switch port.

An IDL file is rejected
=======================

|eddsrecorder| prints ``Error parsing the IDL file`` and stops without processing the capture.
The file must be valid IDL containing the type definitions; check that every type referenced by a struct is defined in
the same file, and review the naming rules in :ref:`user_manual_usage_idl_naming_policy`.

A previous recording disappeared
================================

|eddsrecorder| does not append to an existing database: it empties the discovery tables and drops the topic tables of
the file passed with ``-db`` before processing a capture.
Use a different file name for each capture you want to keep.

The command reports a non-zero exit status on success
=====================================================

The exit status of |eddsrecorder| is not meaningful in this release; the same non-zero value is returned after a
successful run and after a failure.
Scripts should check the ``Number of processed RTPS packets`` line and the ``ERROR<...>`` lines on the console
instead.
