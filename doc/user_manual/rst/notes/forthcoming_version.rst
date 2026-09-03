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
