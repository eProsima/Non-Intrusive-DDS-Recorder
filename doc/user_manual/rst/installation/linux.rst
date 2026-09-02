.. include:: ../exports/alias.include

.. _installation_manual_linux:

###################################
Non-Intrusive DDS Recorder on Linux
###################################

This section describes how to install |eddsrecorder| on the supported Linux distributions, both 32-bit and 64-bit.
Please make sure that the :ref:`installation_manual_requirements` are met before proceeding.

***********************
Downloading the package
***********************

Download the installation package for your system and extract its contents:

.. parsed-literal::

    tar -xzf eProsima_DDSRecorder-\ |release|\ -Linux.tar.gz

The resulting directory contains two folders: ``fastcdr``, with the |efastcdr| library that |eddsrecorder|
depends on, and ``DDSRecorder``, with the application itself.
They must be installed in that order.

****************************
Installing eProsima Fast CDR
****************************

|efastcdr| must be installed in the library directory that matches the architecture of the machine.
For 32-bit machines:

.. code-block:: bash

    cd fastcdr; ./configure --libdir=/usr/lib; make; sudo make install

For 64-bit machines:

.. code-block:: bash

    cd fastcdr; ./configure --libdir=/usr/lib64; make; sudo make install

*****************************************
Installing the Non-Intrusive DDS Recorder
*****************************************

With |efastcdr| in place, install the application:

.. code-block:: bash

    cd DDSRecorder; ./configure; make; sudo make install

**************************
Verifying the installation
**************************

Print the application help to check that the installation succeeded and that every shared library is resolved:

.. code-block:: bash

    DDSRecorder -help

The command prints the list of accepted arguments, described in
:ref:`user_manual_usage_application_arguments`.

If the loader reports that a shared library is missing, review the
:ref:`Linux dependencies <installation_manual_requirements_linux>` and refresh the linker cache with
``sudo ldconfig``.
