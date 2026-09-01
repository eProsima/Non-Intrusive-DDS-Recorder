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
