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

    *   - `LZ4 <https://lz4.org/>`_ and |br|
          `Zstandard <https://facebook.github.io/zstd/>`_
        - Compress the chunks of an |br|
          :term:`MCAP` recording. |br|
          **Only needed for the MCAP** |br|
          **output**; see |br|
          :ref:`user_manual_mcap_output_build`.
        - ``liblz4-dev``, |br|
          ``libzstd-dev``

On Debian based distributions all of them can be installed with a single command:

.. code-block:: bash

    sudo apt install libpcap-dev libsqlite3-dev libboost-all-dev liblz4-dev libzstd-dev

Leaving out the last two only costs the :term:`MCAP` output: a build that cannot find them keeps
working and simply has no ``-mcap`` argument.

|eddsrecorder| also uses the |efastcdr| library to deserialize the :term:`CDR` representation of the recorded samples.
|efastcdr| is distributed together with the application, and :ref:`installation_manual_linux` explains how to install
it.
