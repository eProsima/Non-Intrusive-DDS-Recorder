.. add orphan tag when new info added to this file

:orphan:

###################
Forthcoming Version
###################

This release adds support for capture files whose link layer is not Ethernet:

* Loopback captures using the ``NULL`` and ``LOOP`` link layers, produced by the loopback interfaces of macOS, the
  BSDs and Windows.
* Captures taken on the Linux ``any`` pseudo-interface, which use the *Linux cooked capture* link layers
  ``LINUX_SLL`` and ``LINUX_SLL2``.
* Captures stored with no link layer header, using the ``RAW`` link layer.

The link layer of the capture file is now inspected when the file is opened, and a capture using an unsupported link
layer is reported instead of being processed as if it contained no RTPS traffic.

This release also adds the ``-monitor`` argument, which writes the recording using the *eProsima DDS Record & Replay*
schema instead of the default one.
Each sample is stored as the raw CDR payload, so no data type is required: topics whose TypeCode was never
announced, and whose samples the default schema cannot store, are recorded as well.
See :ref:`user_manual_monitor_schema`.

The recording can also be written as an :term:`MCAP` file, with the new ``-mcap`` argument in place of
``-db``.
This is the format *eProsima DDS Record & Replay* writes, so the result can be read by the tools that
consume its recordings.
See :ref:`user_manual_mcap_output`.

*eProsima Non-Intrusive DDS Recorder* is now built as C++17.
LZ4 and Zstandard are new build dependencies, but only for the MCAP output, which the new
``MCAP_SUPPORT`` CMake option makes optional: it defaults to ``AUTO``, building the MCAP output when
those libraries are available and leaving it out when they are not.
