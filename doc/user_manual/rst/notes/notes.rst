.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _notes:

.. include:: forthcoming_version.rst

##############
Version v1.0.0
##############

This is the first release of |eddsrecorder|.
It provides a command line application that translates the RTPS traffic contained in a :term:`PCAP` capture file into a
:term:`SQLite` database, as described in the :ref:`User Manual <user_manual_introduction>`.

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
        - Fedora 19 32-bit with gcc 4.8.1 |br|
          Fedora 19 64-bit with gcc 4.8.1 |br|
          CentOS 6.4 32-bit with gcc 4.4.7 |br|
          CentOS 6.4 64-bit with gcc 4.4.7

    *   - Windows
        - Windows 7 32-bit |br|
          Windows 7 64-bit

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

|eddsrecorder| was tested against several DDS implementations.

.. list-table:: List of supported DDS implementations
    :header-rows: 1

    *   - DDS Implementation
        - Notes

    *   - RTI DDS 4.5f
        -

    *   - RTI Connext DDS 5.0.0
        -

    *   - OpenDDS 3.3
        - OpenDDS does not send the TypeCode information. |br|
          You need to add at least one RTI DDS node subscribing |br|
          to the topics of interest to enable type discovery, or |br|
          provide the type definitions through an IDL file using |br|
          the ``-idl`` argument.
