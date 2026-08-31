.. include:: ../exports/alias.include

.. _installation_manual_linux:

###################################
Non-Intrusive DDS Recorder on Linux
###################################

This section describes how to install |eddsrecorder| on the supported Linux distributions, both 32-bit and 64-bit.
Please make sure that the :ref:`installation_manual_requirements` are met before proceeding.

Download the installation package for your system:

.. code-block:: text

    eProsima_DDSRecorder-1.1.0-Linux.tar.gz

Extract its content.
First install the |efastcdr| library needed by |eddsrecorder|.
For 32-bit machines:

.. code-block:: bash

    cd fastcdr; ./configure --libdir=/usr/lib; make; make install

For 64-bit machines:

.. code-block:: bash

    cd fastcdr; ./configure --libdir=/usr/lib64; make; make install

Now, install the |eddsrecorder| software:

.. code-block:: bash

    cd DDSRecorder; ./configure; make; make install
