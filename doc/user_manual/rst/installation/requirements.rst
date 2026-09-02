.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _installation_manual_requirements:

##################
Basic Requirements
##################

This section describes the third-party software that |eddsrecorder| needs in order to run.
Once these requirements are met, please refer to :ref:`installation_manual_windows` or
:ref:`installation_manual_linux` to install the application itself.

.. _installation_manual_requirements_windows:

*******
Windows
*******

Latest Microsoft Visual C++ Redistributable package
===================================================

|eddsrecorder| requires the latest *Microsoft Visual C++ Redistributable* package.
The distributed installer checks whether the package is present in the system and, if it is not, prompts the user to
install it.

.. _installation_manual_requirements_linux:

*******************
Linux distributions
*******************

The binary distribution of |eddsrecorder| links against the libraries listed below.
Install them using the package manager of the corresponding Linux distribution.

.. list-table:: Runtime dependencies on Linux
    :header-rows: 1
    :widths: 20 45 35

    *   - Dependency
        - Purpose
        - Debian/Ubuntu package

    *   - `libpcap <https://www.tcpdump.org/>`_
        - Reads the :term:`PCAP` capture file.
        - ``libpcap-dev``

    *   - `SQLite3 <https://www.sqlite.org/>`_
        - Stores the recorded traffic.
        - ``libsqlite3-dev``

    *   - `Boost <https://www.boost.org/>`_
        - Utility libraries |br|
          (*chrono*, *date_time*, *thread* and *system*).
        - ``libboost-all-dev``

On Debian based distributions the three of them can be installed with a single command:

.. code-block:: bash

    sudo apt install libpcap-dev libsqlite3-dev libboost-all-dev

|eddsrecorder| also uses the |efastcdr| library to deserialize the :term:`CDR` representation of the recorded samples.
|efastcdr| is distributed together with the application, and :ref:`installation_manual_linux` explains how to install
it.
