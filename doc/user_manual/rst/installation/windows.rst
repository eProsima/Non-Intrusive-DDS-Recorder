.. include:: ../exports/alias.include

.. _installation_manual_windows:

#####################################
Non-Intrusive DDS Recorder on Windows
#####################################

This section describes how to install |eddsrecorder| on the supported Windows operating systems.
Please make sure that the :ref:`installation_manual_requirements` are met before proceeding.

*****************
Windows 11 32-bit
*****************

Download the installation package for your system:

.. parsed-literal::

    eProsima_DDSRecorder-\ |release|\ -Win32.exe

Execute the installer and follow the onscreen instructions.

*****************
Windows 11 64-bit
*****************

Download the installation package for your system:

.. parsed-literal::

    eProsima_DDSRecorder-\ |release|\ -Win64.exe

Execute the installer and follow the onscreen instructions.

**************************
Verifying the installation
**************************

The installer adds the ``DDSRecorder`` executable to the installation directory.
Open a command prompt in that directory and print the application help to check that the installation succeeded:

.. code-block:: bat

    DDSRecorder -help

The command prints the list of accepted arguments, described in
:ref:`user_manual_usage_application_arguments`.
