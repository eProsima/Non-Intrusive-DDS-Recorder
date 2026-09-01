.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_database_structure:

############################
Generated Database Structure
############################

.. note::

    This section describes the default schema.
    |eddsrecorder| can also write the *DDS Record & Replay* schema, which stores each sample as an
    raw :term:`CDR` payload and needs no data type at all; see
    :ref:`user_manual_monitor_schema`.

|eddsrecorder| writes two kinds of tables into the generated :term:`SQLite` file.
Tables whose name starts with an underscore are created by the application itself and always have the same schema;
every other table is derived from a DDS Topic found in the capture and its columns depend on the topic data type.

* **Discovery Tables**: store the relevant discovery information.

  * ``_topics``: the DDS Topics and their data type information.
  * ``_endpoints``: the DDS endpoints, that is, DataReaders and DataWriters.
  * ``_endpointDiscoveryMessages``: the raw DDS endpoint discovery messages.

* **User Topics Tables**:

  * **Topic Main Tables**: one table per DDS Topic, storing the topic samples using the topic data type schema.

    * ``topicName1``
    * ``topicName2``
    * ...
    * ``topicNameN``

  * **Topic Auxiliary Tables**: for DDS Topics containing variable length fields, such as an array or a sequence,
    auxiliary tables hold the individual element values of each sample.

    * ``topicNameT``

      * ``topicNameT_varLengthFieldName1``
      * ``topicNameT_varLengthFieldName2``
      * ...
      * ``topicNameT_varLengthFieldNameN``

The user topic tables are only created for the topics whose data type could be resolved.
A topic whose :term:`TypeCode` is neither announced in the discovery traffic nor described in the file passed with
``-idl`` appears in ``_topics`` and ``_endpoints`` but gets no table of its own.

.. note::

    The tables are recreated on every run.
    When |eddsrecorder| opens a database file that already contains its tables, the discovery tables are emptied and
    the topic tables are dropped before the new capture is processed.

.. _user_manual_database_structure_discovery_tables:

****************
Discovery Tables
****************

_topics table
=============

|eddsrecorder| creates a table named ``_topics``.
This table stores information about all DDS Topics found in the sniffer trace.

.. list-table:: ``_topics`` table fields
    :header-rows: 1

    *   - Table field
        - Field type
        - Description

    *   - ``topic_name``
        - ``VARCHAR(255)``
        - The name of the discovered DDS Topic, |br|
          exactly as announced on the wire.

    *   - ``type_name``
        - ``VARCHAR(255)``
        - The name of the DDS Topic data type.

    *   - ``typecode``
        - ``TEXT``
        - The TypeCode of the data type rendered |br|
          as human readable IDL.

The ``typecode`` column is the definitive record of the schema |eddsrecorder| used to lay out the corresponding topic
table, which makes it the first thing to inspect when a column is missing or has an unexpected type.

_endpoints table
================

|eddsrecorder| creates a table named ``_endpoints``.
This table stores information about the DataWriters and DataReaders found in the sniffer trace.
Its primary key is the four-field :term:`Guid`, so each endpoint appears exactly once no matter how many times it was
announced.

.. list-table:: ``_endpoints`` table fields
    :header-rows: 1

    *   - Table field
        - Field type
        - Description

    *   - ``rtps_host_id`` |br|
          ``rtps_app_id`` |br|
          ``rtps_instance_id`` |br|
          ``rtps_entity_id``
        - ``UNSIGNED INT``
        - These four fields contain the unique |br|
          identifier of the endpoint. |br|
          The first three are the |br|
          :term:`GuidPrefix` of the participant |br|
          that owns it; the fourth identifies |br|
          the endpoint inside that participant. |br|
          Together they form the primary key.

    *   - ``endpoint_type``
        - ``CHARACTER(10)``
        - Type of entity: ``DataReader`` or |br|
          ``DataWriter``.

    *   - ``topic_name``
        - ``VARCHAR(255)``
        - Topic associated with the entity.

_endpointDiscoveryMessages table
================================

|eddsrecorder| creates a table named ``_endpointDiscoveryMessages``.
This table stores all RTPS messages involved in the endpoint discovery phase, one row per message, keyed by
``message_id``.

.. list-table:: ``_endpointDiscoveryMessages`` table fields
    :header-rows: 1

    *   - Table field
        - Field type
        - Description

    *   - ``message_id``
        - ``INT``
        - Numeric identifier for the message, |br|
          matching the sniffer packet number. |br|
          Primary key of the table.

    *   - ``sniffer_timestamp_sec`` |br|
          ``sniffer_timestamp_usec``
        - ``INT``
        - Sniffer timestamp (seconds, microseconds).

    *   - ``ip_src``
        - ``VARCHAR(15)``
        - Source IP address.

    *   - ``ip_dst``
        - ``VARCHAR(15)``
        - Destination IP address. |br|
          A multicast address here means the |br|
          message was announced to the whole |br|
          domain rather than to a single peer.

    *   - ``src_rtps_host_id`` |br|
          ``src_rtps_app_id`` |br|
          ``src_rtps_instance_id``
        - ``UNSIGNED INT``
        - :term:`GuidPrefix` of the source |br|
          participant.

    *   - ``src_timestamp_sec`` |br|
          ``src_timestamp_nanosec``
        - ``INT``
        - Source timestamp of the discovery message |br|
          (seconds, nanoseconds). |br|
          This timestamp is set when the source |br|
          participant sends the discovery message |br|
          using its own clock.

    *   - ``dst_rtps_host_id`` |br|
          ``dst_rtps_app_id`` |br|
          ``dst_rtps_instance_id``
        - ``UNSIGNED INT``
        - :term:`GuidPrefix` of the destination |br|
          participant. |br|
          These fields are ``NULL`` when the |br|
          discovery message is not addressed to |br|
          a single DomainParticipant.

    *   - ``endpoint_rtps_entity_id``
        - ``UNSIGNED INT``
        - ``rtps_entity_id`` of the announced |br|
          endpoint. |br|
          The endpoint Guid is obtained by |br|
          appending this ID to the source |br|
          participant GuidPrefix.

    *   - ``endpoint_type``
        - ``CHARACTER(10)``
        - This field specifies if the endpoint is |br|
          a ``DataWriter`` or a ``DataReader``.

    *   - ``topic_name``
        - ``VARCHAR(255)``
        - The name of the DDS Topic associated |br|
          with the DataWriter or DataReader.

    *   - ``contains_typecode``
        - ``UNSIGNED TINYINT``
        - ``1`` if the endpoint information |br|
          contains the TypeCode of the topic data |br|
          type, otherwise ``0``. |br|
          A ``0`` means the topic can only be |br|
          recorded if an IDL file is supplied.

.. note::

    The :term:`SPDP` participant announcements are not recorded.
    |eddsrecorder| tracks DDS entities at the endpoint level, so a participant is only visible through the
    GuidPrefix of the endpoints it owns and the samples it sends.

.. _user_manual_database_structure_user_topics_tables:

******************
User Topics tables
******************

.. _user_manual_database_structure_table_names:

Table names
===========

For each discovered DDS Topic whose data type could be resolved, |eddsrecorder| creates a table named after the topic.
Since a DDS topic name may contain characters that are not valid in an unquoted SQL identifier, the following
substitutions are applied to obtain the table name.
Every occurrence of

.. code-block:: text

    ':'   '.'   '-'   ' '

is replaced by the character ``_``.

For example, the topic ``Example HelloWorld`` used in :ref:`user_manual_usage_example` is stored in a table named
``Example_HelloWorld``, and a topic named ``robot.arm-1`` would be stored in ``robot_arm_1``.
The ``_topics`` table always keeps the original, unmodified topic name, so it is the way to map a table back to its
topic.

.. warning::

    Because these substitutions are not reversible, two different topic names may map to the same table name; for
    instance ``a.b`` and ``a-b`` both become ``a_b``.
    When that happens the topic discovered later drops and recreates the table, discarding the rows already written
    for the other topic.
    Rename one of the topics, or record them from separate captures, to record both.

Topic Main Tables
=================

The main table of a topic stores all its data samples, using the following schema:

* Protocol metadata fields, always the same and always first.
* Topic data type fields, derived from the TypeCode as described in :ref:`user_manual_data_types`.

.. _user_manual_database_structure_metadata:

.. list-table:: Topic table protocol metadata fields
    :header-rows: 1

    *   - Table field
        - Field type
        - Description

    *   - ``message_id``
        - ``INT``
        - Numeric identifier for the message, |br|
          matching the sniffer packet number. |br|
          Primary key of the table, and the |br|
          natural way to order samples by |br|
          capture order.

    *   - ``sniffer_timestamp_sec`` |br|
          ``sniffer_timestamp_usec``
        - ``INT``
        - Sniffer timestamp (seconds, microseconds). |br|
          Taken from the capture file, so all |br|
          samples share this clock regardless of |br|
          which node sent them.

    *   - ``ip_src``
        - ``VARCHAR(15)``
        - Source IP address.

    *   - ``ip_dst``
        - ``VARCHAR(15)``
        - Destination IP address.

    *   - ``src_rtps_host_id`` |br|
          ``src_rtps_app_id`` |br|
          ``src_rtps_instance_id``
        - ``UNSIGNED INT``
        - :term:`GuidPrefix` of the participant |br|
          that sent the sample.

    *   - ``src_timestamp_sec`` |br|
          ``src_timestamp_nanosec``
        - ``INT``
        - Source timestamp of the message |br|
          (seconds, nanoseconds). |br|
          This timestamp is set when the source |br|
          participant sends the message using its |br|
          own clock.

    *   - ``dst_rtps_host_id`` |br|
          ``dst_rtps_app_id`` |br|
          ``dst_rtps_instance_id``
        - ``UNSIGNED INT``
        - :term:`GuidPrefix` of the destination |br|
          participant. |br|
          These fields are ``NULL`` when the message |br|
          is not addressed to a single |br|
          DomainParticipant.

.. note::

    The metadata identifies the *participant* that sent a sample, not the individual DataWriter: there is no
    ``src_rtps_entity_id`` column.
    When a participant owns several DataWriters on the same topic, their samples cannot be told apart.
    Joining the three ``src_rtps_*`` columns against ``_endpoints`` resolves the writer whenever the participant owns
    exactly one writer on the topic, as shown in :ref:`user_manual_querying_database`.

Because these names are added in front of every topic table, a data type member with one of these names collides
with them.
See :ref:`user_manual_usage_idl_naming_policy`.

Topic Auxiliary Tables
======================

If a topic contains a variable length field, such as an array or a sequence, an auxiliary table named
``<TopicTableName>_<FieldName>`` holds one row per element of that field, and the main table gets an integer
``<FieldName>_id`` column that links to it.

The complete information of a sample is obtained with an SQL query that joins the auxiliary table with the
corresponding main table on that column.
Please refer to :ref:`user_manual_data_types_sequences_arrays` for the exact schema of these tables and to
:ref:`user_manual_querying_database` for the queries.
