.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _notes:

.. .. include:: forthcoming_version.rst

##############
Version v1.1.0
##############

This release updates |eddsrecorder| to build against |efastcdr| v2.4.0.

.. _notes_system_requirements:

*******************
System requirements
*******************

Supported operating systems
===========================

This section describes the operating systems supported by |eddsrecorder|.

.. list-table:: List of supported operating systems
    :header-rows: 1

    *   - Platform
        - Operating System

    *   - Linux
        - Ubuntu Noble 32-bit with gcc 13.3.0 |br|
          Ubuntu Noble 64-bit with gcc 13.3.0

    *   - Windows
        - Windows 11 32-bit |br|
          Windows 11 64-bit

For more information about how to install |eddsrecorder|, read the
:ref:`Installation Manual <installation_manual_requirements>`.

If you are interested in supporting other operating systems, please
`contact us <mailto:info@eprosima.com?subject=DDS%20Recorder%20Platform%20Request>`__.

Supported databases
===================

|eddsrecorder| uses an external database to store information.
Currently only the SQLite database is supported.
It is a lightweight database and external configuration is not needed.

If you are interested in supporting other databases, please
`contact us <mailto:info@eprosima.com?subject=DDS%20Recorder%20DB%20Request>`__.

Supported DDS implementations
=============================

|eddsrecorder| works at the wire protocol level, so the traffic and the endpoint discovery of any DDS implementation
that speaks :term:`RTPS` over UDP/IPv4 is recorded, regardless of the vendor.

What does depend on the implementation is the **automatic data type discovery**.
|eddsrecorder| obtains the data type schema from the :term:`TypeCode` parameter of the :term:`SEDP` endpoint
announcements, and that parameter is a vendor extension rather than a part of the RTPS specification.
For an implementation that does not include it, the data types must be supplied with an :term:`IDL` file through the
``-idl`` argument, as described in :ref:`user_manual_usage_idl_naming_policy`.
This includes |efastdds|, which announces its types using a different mechanism.

The ``contains_typecode`` column of the ``_endpointDiscoveryMessages`` table reports, for each endpoint found in a
capture, whether its announcement carried a TypeCode.
It is the quickest way to find out whether a given system needs an IDL file; see
:ref:`user_manual_querying_database_entities`.

Supported capture formats
=========================

|eddsrecorder| reads the capture formats supported by :term:`libpcap`, which covers both the classic ``pcap`` format
and the ``pcapng`` format written by recent versions of *Wireshark*.
The capture must contain complete packets and use the transport layers listed in
:ref:`user_manual_limitations_scope`.

The following link layers are supported, which covers Ethernet interfaces, loopback interfaces on every supported
platform, and the Linux ``any`` pseudo-interface:

.. list-table:: List of supported link layers
    :header-rows: 1
    :widths: 30 70

    *   - pcap link layer
        - Typical source

    *   - ``EN10MB``
        - Ethernet and Wi-Fi interfaces, and the Linux ``lo`` interface.

    *   - ``NULL`` |br|
          ``LOOP``
        - Loopback interfaces on macOS, the BSDs and Windows.

    *   - ``LINUX_SLL`` |br|
          ``LINUX_SLL2``
        - The Linux ``any`` pseudo-interface.

    *   - ``RAW``
        - Tunnel interfaces and captures stored without a link layer header.

A capture using any other link layer is reported when the file is opened.
See :ref:`user_manual_limitations_link_layers`.

.. include:: v1.0.0.rst
