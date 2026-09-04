.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_database_structure:

################
Queryable schema
################

The ``-queryable`` argument does not choose a schema, it adds one.
The *DDS Record & Replay* tables described in :ref:`user_manual_monitor_schema` are written whatever the arguments,
and ``-queryable`` puts more tables beside them.
A recording made with it is therefore still a valid *DDS Record & Replay* database, and can still be replayed.

What it adds is of two kinds:

* **One table per DDS Topic**, whose columns are the members of the topic data type, so the samples can be read with
  ordinary SQL instead of decoding a :term:`CDR` blob.
  That is what the name refers to, and it is the trade-off: a topic needs its data type to be known, from the file
  passed with ``-idl``, or it gets no table.

* **The packet level tables**, holding what a capture reveals and the *DDS Record & Replay* schema has no column for:
  which packet carried which sample, and between which addresses.

.. note::

    A topic without a table is not a loss.
    Its samples are in ``Messages`` as :term:`CDR`, exactly as they would be without ``-queryable``.

.. _user_manual_database_structure_discovery_tables:

*******************
Packet level tables
*******************

Endpoints
=========

One row per DDS :term:`DataWriter` or :term:`DataReader` announced in the discovery traffic.

.. list-table::
    :header-rows: 1
    :widths: 24 16 60

    *   - Column
        - Type
        - Description

    *   - ``guid``
        - TEXT
        - :term:`Guid` of the endpoint, spelled exactly as |br|
          ``Messages.writer_guid`` spells a writer. |br|
          Primary key.

    *   - ``kind``
        - TEXT
        - ``DataWriter`` or ``DataReader``.

    *   - ``topic``
        - TEXT
        - Name of the DDS Topic the endpoint serves.

    *   - ``type``
        - TEXT
        - Name of the DDS Topic data type.

Because ``guid`` uses the same spelling as ``Messages.writer_guid``, the two join without any conversion:

.. code-block:: sql

    SELECT e.kind, e.topic, COUNT(m.sequence_number)
        FROM Endpoints e LEFT JOIN Messages m ON m.writer_guid = e.guid
        GROUP BY e.guid;

DiscoveryMessages
=================

One row per discovery packet the capture holds, not per endpoint: an endpoint announced repeatedly, or announced to
several destinations, produced several packets.

.. list-table::
    :header-rows: 1
    :widths: 24 16 60

    *   - Column
        - Type
        - Description

    *   - ``packet_id``
        - INTEGER
        - Ordinal of the packet inside the capture |br|
          file. Primary key.

    *   - ``log_time``
        - DATETIME
        - When the sniffer saw the packet.

    *   - ``publish_time``
        - DATETIME
        - Source timestamp carried by the packet.

    *   - ``ip_src``
        - TEXT
        - Source IPv4 address.

    *   - ``ip_dst``
        - TEXT
        - Destination IPv4 address.

    *   - ``dst_guid_prefix``
        - TEXT
        - GuidPrefix the packet was addressed to, |br|
          or ``NULL`` when it carried no |br|
          ``INFO_DST`` and so was addressed to |br|
          every participant.

    *   - ``endpoint_guid``
        - TEXT
        - The endpoint announced, referencing |br|
          ``Endpoints.guid``.

    *   - ``kind``
        - TEXT
        - ``DataWriter`` or ``DataReader``.

The announcing participant is the one that owns the endpoint, so its GuidPrefix is the prefix half of
``endpoint_guid`` and has no column of its own.

MessagesCapture
===============

One row per packet that carried a user sample.

.. list-table::
    :header-rows: 1
    :widths: 24 16 60

    *   - Column
        - Type
        - Description

    *   - ``packet_id``
        - INTEGER
        - Ordinal of the packet inside the capture |br|
          file. Primary key.

    *   - ``writer_guid``
        - TEXT
        - Together with ``sequence_number``, |br|
          references ``Messages``.

    *   - ``sequence_number``
        - INTEGER
        - Sequence number of the sample.

    *   - ``log_time``
        - DATETIME
        - When the sniffer saw the packet.

    *   - ``ip_src``
        - TEXT
        - Source IPv4 address.

    *   - ``ip_dst``
        - TEXT
        - Destination IPv4 address.

    *   - ``dst_guid_prefix``
        - TEXT
        - GuidPrefix the packet was addressed to, |br|
          or ``NULL``.

This table is the reason ``-queryable`` sees more than ``Messages`` does.
``Messages`` is keyed on ``(writer_guid, sequence_number)``, so a sample that traveled twice, because it was sent
both as multicast and as unicast or because the writer repaired it, appears once there.
Here each transmission is a row, so the repetition the capture witnessed survives:

.. code-block:: sql

    SELECT writer_guid, sequence_number, COUNT(*) FROM MessagesCapture
        GROUP BY 1, 2 HAVING COUNT(*) > 1;

DataTables
==========

The registry naming the per topic tables.

.. list-table::
    :header-rows: 1
    :widths: 24 16 60

    *   - Column
        - Type
        - Description

    *   - ``topic``
        - TEXT
        - Name of the DDS Topic.

    *   - ``type``
        - TEXT
        - Name of the DDS Topic data type.

    *   - ``member_path``
        - TEXT
        - Empty for the topic's own table, |br|
          otherwise the collection member the |br|
          table holds.

    *   - ``table_name``
        - TEXT
        - The SQL name of the table.

.. _user_manual_database_structure_user_topics_tables:

******************
User Topics tables
******************

.. _user_manual_database_structure_table_names:

Table names
===========

A DDS topic name may contain characters that are not valid in an unquoted SQL identifier, so the table of a topic is
named ``Data_`` followed by the topic name with every character outside ``A-Z``, ``a-z``, ``0-9`` and ``_`` replaced
by an underscore.
For example, the topic ``Example HelloWorld`` is stored in a table named ``Data_Example_HelloWorld``.

Two different topic names can end up with the same identifier that way.
Rather than let the second silently replace the first, |eddsrecorder| gives it a numeric suffix, and records every
table in ``DataTables``:

.. code-block:: sql

    SELECT table_name FROM DataTables WHERE topic = 'Example HelloWorld' AND member_path = '';

Read the name from there rather than reproducing the substitution by hand; it is the only way that stays correct when
a suffix has been added.

Topic Main Tables
=================

The main table of a topic holds one row per sample: two key columns, then one column per member of the data type.

.. list-table::
    :header-rows: 1
    :widths: 24 16 60

    *   - Column
        - Type
        - Description

    *   - ``writer_guid``
        - TEXT
        - Together with ``sequence_number``, the |br|
          primary key, referencing ``Messages``.

    *   - ``sequence_number``
        - INTEGER
        - Sequence number of the sample.

    *   - *one per member*
        - *depends*
        - The members of the data type, |br|
          flattened as described below.

Everything the recording shares with the *DDS Record & Replay* schema, from the timestamps to the topic name, stays in
``Messages`` instead of being repeated in every topic table.
Reading a sample beside those columns is therefore a join, and the ``_flat`` view created next to each table does it
for you:

.. code-block:: sql

    SELECT log_time, counter, message FROM Data_Example_HelloWorld_flat ORDER BY log_time;

A nested structure is flattened into the same table, its member names prefixed with the path that reaches them, so a
member ``ins`` of type ``Inside`` with a member ``count`` becomes the column ``ins_count``.
Member names are emitted as quoted identifiers, so a member named after an SQLite keyword needs no renaming.

A union adds a ``<path>_discriminator`` column holding the value that selected the branch, and one column per branch.
The columns of the branches a sample did not take are ``NULL``.

Topic Auxiliary Tables
======================

An array or a sequence member cannot fit in one column, so it gets a table of its own, named after the main table and
the member: ``Data_Example_Arrays_ocarray`` for the member ``ocarray``.
It holds one row per element.

.. list-table::
    :header-rows: 1
    :widths: 24 16 60

    *   - Column
        - Type
        - Description

    *   - ``writer_guid``
        - TEXT
        - Together with ``sequence_number``, |br|
          identifies the sample the element |br|
          belongs to.

    *   - ``sequence_number``
        - INTEGER
        - Sequence number of the sample.

    *   - ``index_0`` ... ``index_n``
        - INTEGER
        - Position of the element. One column per |br|
          array dimension; a sequence has one.

    *   - ``value``
        - *depends*
        - The element, when it is a simple type.

    *   - *one per member*
        - *depends*
        - When the element is a structure, its |br|
          members are flattened here instead of |br|
          a single ``value`` column.

The key columns are the same as the main table's, so an element joins back to its sample, and through it to
``Messages``:

.. code-block:: sql

    SELECT m.log_time, a.index_0, a.value
        FROM Data_Example_Arrays_ocarray a
        JOIN Messages m USING (writer_guid, sequence_number)
        ORDER BY m.log_time, a.index_0;

*******************
Unsupported members
*******************

A member whose type has no column representation makes the whole topic unrepresentable, and no table is created for
it. That covers maps, bitsets, bitmasks, 128 bit floats, wide strings, and a collection nested directly inside
another collection.
The samples are still recorded as :term:`CDR` in ``Messages``, and the reason is printed on the console.
