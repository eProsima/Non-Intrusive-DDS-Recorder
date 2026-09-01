.. include:: ../exports/alias.include

.. _glossary:

########
Glossary
########

Non-Intrusive DDS Recorder nomenclature
=======================================

.. glossary::

    PCAP
        **Packet Capture**.
        Standard file format used by network sniffers, such as *Wireshark*, to store the captured network traffic.
        |eddsrecorder| takes a PCAP file as input.

    SQLite
        Lightweight, serverless and self-contained SQL database engine.
        The output of |eddsrecorder| is a SQLite database file that requires no external configuration.

    TypeCode
        Representation of the definition of a data type that some DDS implementations send as part of the discovery
        information.
        |eddsrecorder| uses it to build the tables that store the user data of each topic.
        When it is not present in the discovery traffic, an :term:`IDL` file must be supplied instead.

    snaplen
        **Snapshot length**.
        Maximum number of bytes that a network sniffer stores for each packet.
        A capture taken with a limited snaplen contains truncated packets, which |eddsrecorder| discards, so captures
        must be taken with an unlimited snapshot length.

DDS nomenclature
================

.. glossary::

    CDR
        **Common Data Representation**.
        Serialization format defined by the OMG that DDS uses to encode samples on the wire.
        |eddsrecorder| deserializes the CDR payload of each sample to fill in the columns of the topic table.

    DataReader
        DDS element that subscribes to a specific Topic.
        It belongs to one and only one Participant, and it is uniquely identified by a Guid.

        See `Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/subscriber/dataReader/dataReader.html>`__
        for further information.

    DataWriter
        DDS entity that publishes data in a specific Topic.
        It belongs to one and only one Participant, and it is uniquely identified by a Guid.

        See `Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/publisher/dataWriter/dataWriter.html>`__
        for further information.

    Domain Id
        The Domain Id is a virtual partition for DDS networks.
        Only DomainParticipants with the same Domain Id are able to communicate with each other.
        DomainParticipants in different domains will not even discover each other.

        See `Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/domain/domain.html>`__
        for further information.

    DomainParticipant
        A DomainParticipant is the entry point of the application to a DDS domain.
        Every DomainParticipant is linked to a single domain from its creation, and cannot change such domain.
        It also acts as a factory for Publisher, Subscriber and Topic.

        See `Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/domain/domainParticipant/domainParticipant.html>`__
        for further information.

    Endpoint
        DDS element that publishes or subscribes in a specific Topic.
        Endpoint kinds are *DataWriter* or *DataReader*.

    Guid
        **Global Unique Identifier**.
        It contains a GuidPrefix and an EntityId.
        The EntityId uniquely identifies sub-entities inside a Participant.
        It identifies uniquely a DDS entity (DomainParticipant, DataWriter or DataReader).

    GuidPrefix
        Global Unique Identifier shared by a Participant and all its sub-entities.
        It identifies uniquely a DDS Participant.

    IDL
        **Interface Definition Language**.
        Language defined by the OMG used to describe the data types exchanged over DDS.
        It can be supplied to |eddsrecorder| when the DDS implementation under study does not send TypeCode
        information.

    QoS
        **Quality of Service**.
        Set of policies that configure the behavior of a DDS entity, such as its reliability or its durability.
        QoS policies are announced during discovery but are not recorded by |eddsrecorder|.

    RTPS
        **Real-Time Publish-Subscribe**.
        Wire protocol defined by the OMG that DDS implementations use to communicate over the network.
        |eddsrecorder| dissects this protocol to reconstruct the DDS traffic.

    Sample
        A single data value published on a :term:`Topic`.
        |eddsrecorder| stores one row per sample *transmission* observed in the capture, so a sample sent to several
        destinations produces several rows.

    SEDP
        **Simple Endpoint Discovery Protocol**.
        Phase of the RTPS discovery in which participants announce their :term:`DataWriter`\ s and
        :term:`DataReader`\ s, together with the topic and data type each of them uses.
        |eddsrecorder| builds its discovery tables from these messages.

    SPDP
        **Simple Participant Discovery Protocol**.
        Phase of the RTPS discovery in which :term:`DomainParticipant`\ s announce their own existence, before
        exchanging endpoint information through :term:`SEDP`.
        These announcements are not recorded by |eddsrecorder|.

    Topic
        DDS isolation abstraction to encapsulate subscriptions and publications.
        Each Topic is uniquely identified by a topic name and a topic type name (name of the data type it transmits).

        See `Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/topic/topic.html>`__
        for further information.

Networking nomenclature
=======================

.. glossary::

    LAN
        **Local Area Network**

    libpcap
        Library used to read packet capture files.
        |eddsrecorder| relies on it to iterate over the packets of the :term:`PCAP` file.

    PCAP file rotation
        Practice of splitting a long capture into several files.
        |eddsrecorder| processes one file per run, so each file produces its own database.

    Switch debug port
        Port of a network switch configured to mirror the traffic of the other ports.
        Sniffing this port is required to capture all the traffic of a DDS network, and not only the traffic directed
        to the node where the sniffer runs.
