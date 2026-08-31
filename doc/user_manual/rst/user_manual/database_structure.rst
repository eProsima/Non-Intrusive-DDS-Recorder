.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_database_structure:

############################
Generated Database Structure
############################

|eddsrecorder| creates a set of tables with the discovery information and the user data traffic:

* **Discovery Tables**: used to store relevant discovery information.

  * ``_topics`` table: stores the DDS Topics and their data type information.
  * ``_endpoints`` table: stores DDS endpoint information (DataReaders and DataWriters).
  * ``_endpointDiscoveryMessages`` table: stores DDS endpoint discovery messages.

* **User Topics Tables**:

  * **Topic Main Tables**: a table per DDS Topic storing the topic messages using their data type schema.

    * ``topicName1``
    * ``topicName2``
    * ...
    * ``topicNameN``

  * **Topic Auxiliary Tables**: for DDS Topics containing variable length fields, such as an array or a sequence,
    auxiliary tables are created to store the field values of each topic message.

    * ``topicNameT``

      * ``topicNameT_varLengthFieldName1``
      * ``topicNameT_varLengthFieldName2``
      * ...
      * ``topicNameT_varLengthFieldNameN``

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
        - The name of the discovered DDS Topic.

    *   - ``type_name``
        - ``VARCHAR(255)``
        - The name of the DDS Topic data type.

    *   - ``typecode``
        - ``TEXT``
        - The TypeCode of the data type in a human readable format.

_endpoints table
================

|eddsrecorder| creates a table named ``_endpoints``.
This table stores information about the DataWriters and DataReaders found in the sniffer trace.

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
          identifier for each discovered entity.

    *   - ``endpoint_type``
        - ``CHARACTER(10)``
        - Type of entity: DataReader or DataWriter.

    *   - ``topic_name``
        - ``VARCHAR(255)``
        - Topic associated with the entity.

_endpointDiscoveryMessages table
================================

|eddsrecorder| creates a table named ``_endpointDiscoveryMessages``.
This table stores all RTPS messages involved in the endpoint discovery phase.

.. list-table:: ``_endpointDiscoveryMessages`` table fields
    :header-rows: 1

    *   - Table field
        - Field type
        - Description

    *   - ``message_id``
        - ``INT``
        - Numeric identifier for the message, |br|
          matching the sniffer packet number.

    *   - ``sniffer_timestamp_sec`` |br|
          ``sniffer_timestamp_usec``
        - ``INT``
        - Sniffer timestamp (seconds, microseconds).

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
        - RTPS GUID (Global Unique ID) of the |br|
          source participant.

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
        - RTPS GUID (Global Unique ID) of the |br|
          destination participant. |br|
          These fields could be empty if the |br|
          discovery message is not delivered to |br|
          only one DomainParticipant.

    *   - ``endpoint_rtps_entity_id``
        - ``UNSIGNED INT``
        - ``rtps_entity_id`` of the endpoint. |br|
          The endpoint GUID is obtained by |br|
          appending this ID to the source |br|
          participant GUID.

    *   - ``endpoint_type``
        - ``CHARACTER(10)``
        - This field specifies if the endpoint is |br|
          a DataWriter or a DataReader.

    *   - ``topic_name``
        - ``VARCHAR(255)``
        - The name of the DDS Topic associated |br|
          with the DataWriter or DataReader.

    *   - ``contains_typecode``
        - ``UNSIGNED TINYINT``
        - ``1`` if the information of the endpoint |br|
          contains the TypeCode of the topic data |br|
          type, otherwise ``0``.

.. _user_manual_database_structure_user_topics_tables:

******************
User Topics tables
******************

Topic Main Tables
=================

For each discovered DDS Topic, |eddsrecorder| creates a table named after the topic.
The following characters are not allowed in the table name and are replaced by the character ``_``:

.. code-block:: text

    ':'  '.'  '-'

This table stores all data samples of the topic, using the following schema:

* Protocol metadata fields.
* Topic data type fields.

.. list-table:: Topic table protocol metadata fields
    :header-rows: 1

    *   - Table field
        - Field type
        - Description

    *   - ``message_id``
        - ``INT``
        - Numeric identifier for the message, |br|
          matching the sniffer packet number.

    *   - ``sniffer_timestamp_sec`` |br|
          ``sniffer_timestamp_usec``
        - ``INT``
        - Sniffer timestamp (seconds, microseconds).

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
        - RTPS GUID (Global Unique ID) of the |br|
          source participant.

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
        - RTPS GUID (Global Unique ID) of the |br|
          destination participant. |br|
          These fields could be empty if the |br|
          message is not delivered to only one |br|
          DomainParticipant.

Topic Auxiliary Tables
======================

If a topic contains a variable length field, such as an array or a sequence, an auxiliary table is created to store the
field values of each topic message.
The complete information of a sample can be obtained using an SQL query that combines these auxiliary tables with the
corresponding main tables.
Please refer to :ref:`user_manual_data_types_sequences_arrays`.
