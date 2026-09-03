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

This release changes the database schema a recording uses by default.

The *eProsima DDS Record & Replay* schema is now the **default**.
Each sample is stored as its raw CDR payload, so no data type is required at all: a topic whose TypeCode was never
announced, and for which no IDL file was supplied, is now recorded like any other.
See :ref:`user_manual_monitor_schema`.

The previous schema, one table per DDS Topic with one column per data type member, is still available through the new
``-queryable`` argument.
See :ref:`user_manual_database_structure`.

.. warning::

    The ``-monitor`` argument has been **removed**, since the schema it selected is now the default.
    A command line still passing it is refused with a message explaining the replacement: drop the argument to keep
    getting that schema, or pass ``-queryable`` for the previous one.
