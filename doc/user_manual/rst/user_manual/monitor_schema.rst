.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_monitor_schema:

######################
Record & Replay schema
######################

|eddsrecorder| can write its recording in a second, fixed schema instead of the default one, by
passing the ``-monitor`` argument:

.. code-block:: bash

    DDSRecorder -monitor -db session.db capture.pcap

This is the same schema that *eProsima DDS Record & Replay* writes — the tables, the columns and the
keys match it, with the single addition of the ``Types.idl`` column described below — so a recording
made this way is meant to be opened with the *eProsima DDS Monitor* and replayed with
``ddsreplayer``.
The default schema is unchanged and remains what you get without the argument; see
:ref:`user_manual_database_structure`.

.. _user_manual_monitor_schema_differences:

***********************
Why you might prefer it
***********************

The two schemas store the same traffic in opposite shapes.
The default one deserializes every sample and gives each DDS Topic a table whose columns are the
members of its data type.
This schema has a single ``Messages`` table in which the sample is stored as the untouched
:term:`CDR` payload.

That difference has three consequences worth knowing:

* **No data type is required.**
  Nothing is deserialized, so a topic is recorded even when its :term:`TypeCode` was never announced
  and no IDL file was supplied. In the default schema such a topic gets no table at all.

* **Any encapsulation is recorded.**
  The default schema stores a sample only when it is encoded as plain CDR; this one stores the bytes
  whatever their encapsulation, so extended CDR payloads are captured too.

* **The recording can be replayed.**
  ``ddsreplayer`` selects the samples that carry a payload, which the default schema cannot provide.

What you give up is the ability to query individual members with SQL, since the payload is an opaque
blob until something decodes it.

.. note::

    ``-idl`` is not needed with ``-monitor``, but it is still honored.
    When supplied it is used only to fill in the ``Types.idl`` column for topics whose data type was
    not announced in the capture; it can never change the recorded payload.

.. _user_manual_monitor_schema_tables:

**********
The tables
**********

Six tables are created, and no others.
The discovery tables of the default schema are not written.

.. list-table::
    :header-rows: 1
    :widths: 26 74

    *   - Table
        - Contents

    *   - ``Messages``
        - One row per recorded sample.

    *   - ``Topics``
        - One row per discovered DDS Topic.

    *   - ``Types``
        - One row per data type.

    *   - ``Partitions``
        - A single row holding the empty partition.

    *   - ``TopicsPartitions``
        - Associates each topic with that partition.

    *   - ``MessagesPartitions``
        - Associates each message with that partition.

Messages table
==============

.. list-table:: ``Messages`` table fields
    :header-rows: 1
    :widths: 24 16 60

    *   - Table field
        - Field type
        - Description

    *   - ``writer_guid``
        - ``TEXT``
        - :term:`Guid` of the publishing |br|
          DataWriter, as |br|
          ``<prefix>|<entity>``. The prefix is |br|
          twelve zero padded hexadecimal |br|
          bytes; the entity id is four |br|
          hexadecimal bytes that are not zero |br|
          padded. Together with |br|
          ``sequence_number`` it is the |br|
          primary key.

    *   - ``sequence_number``
        - ``INTEGER``
        - RTPS sequence number the writer |br|
          assigned to the sample.

    *   - ``data_json``
        - ``TEXT``
        - Always empty: |eddsrecorder| never |br|
          deserializes the sample.

    *   - ``data_cdr``
        - ``BLOB``
        - The serialized sample exactly as it |br|
          was sent, including its four byte |br|
          encapsulation header.

    *   - ``data_cdr_size``
        - ``INTEGER``
        - Size of ``data_cdr`` in bytes, header |br|
          included.

    *   - ``topic`` |br|
          ``type``
        - ``TEXT``
        - Name of the DDS Topic and of its data |br|
          type, recovered from the discovery |br|
          traffic.

    *   - ``key``
        - ``TEXT``
        - Always ``{}``: the instance key would |br|
          require decoding the sample.

    *   - ``log_time``
        - ``DATETIME``
        - When the sniffer captured the packet, |br|
          as ``YYYY-MM-DD HH:MM:SS.nnnnnnnnn`` |br|
          in UTC.

    *   - ``publish_time``
        - ``DATETIME``
        - When the publishing participant sent |br|
          the sample, taken from the RTPS |br|
          source timestamp, in the same format.

.. important::

    ``(writer_guid, sequence_number)`` is the primary key, which removes duplicates for free.
    A sample that appears several times in the capture, because it was seen both as multicast and as
    unicast or because the writer repaired it, is stored once.
    A row count is therefore a count of distinct samples, unlike the default schema where each row is
    one observed transmission.
    Compare :ref:`user_manual_querying_database_samples`.

Topics and Types tables
=======================

.. list-table::
    :header-rows: 1
    :widths: 30 70

    *   - Table field
        - Description

    *   - ``Topics.name`` |br|
          ``Topics.type``
        - Name of the DDS Topic and of its data type, as announced. |br|
          Unlike the default schema, the topic name is stored |br|
          verbatim and is never used as an SQL identifier, so none |br|
          of the character substitutions described in |br|
          :ref:`user_manual_database_structure_table_names` apply.

    *   - ``Topics.qos``
        - The *DDS Record & Replay* default policies. |br|
          |eddsrecorder| extracts no QoS from the discovery traffic.

    *   - ``Types.name``
        - Name of the data type.

    *   - ``Types.idl``
        - The data type rendered as IDL, whether it was announced |br|
          in the capture or described in the file given with |br|
          ``-idl``. Empty when neither provided it. |br|
          Nothing in the tool reads it back. |br|
          **This column does not exist in a recording made by** |br|
          **DDS Record & Replay**; see the note below.

    *   - ``Types.information`` |br|
          ``Types.object``
        - Always empty. These columns would hold a serialized |br|
          ``TypeIdentifier`` and ``TypeObject``, neither of which |br|
          the RTPS traffic carries. The *DDS Monitor* discards a |br|
          type whose ``object`` does not decode, so they are left |br|
          empty rather than filled with something else.

    *   - ``is_ros2_topic`` |br|
          ``is_ros2_type``
        - Always ``false``.

.. note::

    ``Types.idl`` is the one place where this schema departs from the one *DDS Record & Replay*
    writes.
    The two columns that schema has for type information both expect base64 of a serialized
    ``TypeIdentifier`` or ``TypeObject``, and the RTPS traffic carries neither, so the IDL text gets
    a column of its own.
    The addition is harmless to other tools: a reader that selects the original columns by name
    never sees it, and the column has a default so that a writer unaware of it can still insert a
    type.

.. _user_manual_monitor_schema_querying:

********
Querying
********

The recording is still an ordinary SQLite file.
Listing what was captured needs no type information:

.. code-block:: sql

    SELECT t.name, t.type, COUNT(m.sequence_number) AS samples
    FROM Topics t LEFT JOIN Messages m ON m.topic = t.name AND m.type = t.type
    GROUP BY t.name, t.type
    ORDER BY samples DESC;

The payload itself is opaque to SQL, but its size is not, which is often enough to characterize
traffic:

.. code-block:: sql

    SELECT topic, COUNT(*) AS samples, MIN(data_cdr_size) AS min_bytes,
           MAX(data_cdr_size) AS max_bytes, SUM(data_cdr_size) AS total_bytes
    FROM Messages GROUP BY topic;

To read the values inside a sample, open the database with the *DDS Monitor*, or decode ``data_cdr``
with the type support generated from the corresponding IDL.
