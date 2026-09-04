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

The *eProsima DDS Record & Replay* schema is now the **default**, and is written whatever the arguments.
Each sample is stored as its raw CDR payload, so no data type is required at all: a topic for which no IDL file was
supplied is recorded like any other.
See :ref:`user_manual_monitor_schema`.

``-queryable`` no longer selects a different schema, it **adds** to that one.
It keeps the *DDS Record & Replay* tables, so a recording made with it can still be replayed, and puts beside them:

* One table per DDS Topic, with one column per data type member, keyed on ``(writer_guid, sequence_number)`` so each
  row points back at its ``Messages`` row. A ``_flat`` view joins the two back together.
* ``DataTables``, a registry naming those tables, so the substitution that turns a topic name into an SQL identifier
  never has to be reproduced by hand, and two topics that would collide no longer overwrite each other.
* ``Endpoints``, ``DiscoveryMessages`` and ``MessagesCapture``, holding what the capture reveals and the
  *DDS Record & Replay* schema has no column for: which packet carried which sample, and between which addresses.

See :ref:`user_manual_database_structure`.

``MessagesCapture`` keeps every transmission of a sample.
A sample seen twice, because it traveled both as multicast and as unicast or because the writer repaired it, was
previously counted as a duplicate and discarded; it is now a row of its own.

Support for **TypeCode has been removed**.
The vendor specific TypeCode parameter of the endpoint announcements is no longer read, and the data types now come
from the file given with ``-idl``, which is the only source.
A capture recorded without one is still complete: it simply carries no type description and gets no per-topic table.

Sequences and arrays of user defined structures are now supported, and their elements are stored with the members of
the structure flattened into columns.
Member names are emitted as quoted SQL identifiers, so a member named after an SQLite keyword no longer prevents a
topic from being recorded.

.. warning::

    The ``-monitor`` argument has been **removed**, since the schema it selected is now the default.
    A command line still passing it is refused with a message explaining the replacement: drop the argument to keep
    getting that schema, or pass ``-queryable`` to add the per-topic tables.

.. warning::

    The ``-tcMaxSize`` argument has been **removed** together with the TypeCode support it configured.
    It had no effect in previous releases.
