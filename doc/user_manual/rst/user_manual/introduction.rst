.. include:: ../exports/alias.include

.. _user_manual_introduction:

############
Introduction
############

|eddsrecorder| is a tool that allows users to record DDS network traffic.
By using a non-intrusive mechanism it allows users to test, analyze or log their DDS systems without adding any new DDS
participant or service, ensuring the real behavior and timing is being recorded.

************
How it works
************

|eddsrecorder| records DDS traffic by sniffing the DDS wire protocol (:term:`RTPS`) through the switch debug port.
The tool dissects the protocol and builds a complete database of all the DDS entities
(:term:`DomainParticipant`\ s, Publishers, Subscribers and :term:`Topic`\ s), data types and all the exchanged messages.

|eddsrecorder| does not just record raw data: it builds a message table for each DDS Topic, using the same fields as the
corresponding DDS Topic data type.

A sniffer such as `Wireshark <https://www.wireshark.org/>`_ is needed to save the network traffic into a standard packet
capture (:term:`PCAP`) file.
|eddsrecorder| later parses the file to translate the RTPS messages into a human readable format and store them in a
:term:`SQLite` database.
In order to get all the traffic in your network you should sniff your switch debug port, otherwise you would get just
the traffic directed to the node where the sniffer is running.

.. note::

    Future releases will include a built-in sniffer to process the network packets in real time.

DDS uses an automated process to discover all the DDS entities in your network, including topic names and data types.
|eddsrecorder| analyzes the discovery traffic to build a set of tables in a database, and uses the data type schema to
store the DDS user data traffic later.

To get the data type information, |eddsrecorder| searches for the data type definition (:term:`TypeCode`) in the
discovery messages.
As not all implementations of DDS send TypeCodes over the network, users are advised to check the
:ref:`Release Notes <notes>` for a list of supported implementations.

When the DDS implementation under study does not send this information, an :term:`IDL` file containing the definition
of the data types used in the captured system can be supplied instead through the ``-idl`` command line argument.
See :ref:`user_manual_usage_idl_naming_policy` for the naming rules such a file must follow.
