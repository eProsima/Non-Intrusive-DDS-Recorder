.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_mcap_output:

###########
MCAP output
###########

|eddsrecorder| can write the recording as an :term:`MCAP` file instead of a SQLite database, by
passing ``-mcap`` in place of ``-db``:

.. code-block:: bash

    DDSRecorder -mcap session.mcap capture.pcap

MCAP is the format *eProsima DDS Record & Replay* writes itself and *eProsima DDS Monitor* reads.
A recording made this way is a single self-contained file with no SQL involved.

.. warning::

    ``-db`` and ``-mcap`` are mutually exclusive, since each names the output.
    Passing both is refused before anything is written.
    Passing neither keeps the current default, a ``dump.db`` database in the default schema.

As with :ref:`user_manual_monitor_schema`, each sample is stored as its raw :term:`CDR` payload, so
no data type is needed to record a topic and ``-idl`` is never required.
When an IDL file is supplied it only fills in the type description, exactly as it fills the
``Types.idl`` column of the database.

.. _user_manual_mcap_output_build:

**************************
Availability in your build
**************************

The MCAP output is optional, because it needs the LZ4 and Zstandard development files that the
MCAP library bundled with the application compresses its chunks with.
The ``MCAP_SUPPORT`` CMake option decides whether it is built:

.. list-table::
    :header-rows: 1
    :widths: 16 84

    *   - Value
        - Meaning

    *   - ``AUTO``
        - The default. Build the MCAP output when LZ4 and Zstandard are |br|
          found, and quietly do without it when they are not, so the build |br|
          never fails over MCAP.

    *   - ``ON``
        - Require them. Configuration fails, naming the packages to install, |br|
          if either is missing.

    *   - ``OFF``
        - Never build the MCAP output. The two libraries are not even |br|
          looked for.

Configuration reports which way it went, as ``MCAP output enabled`` or ``MCAP output disabled``.

To find out whether a binary you already have supports it, ask for the help: ``-mcap`` is listed
only when it is available.
Passing ``-mcap`` to a build without it is refused, and says so:

.. code-block:: text

    Error: -mcap is not available: this build has no MCAP support.
           Rebuild with -DMCAP_SUPPORT=ON.

The database outputs are unaffected either way.

.. _user_manual_mcap_output_contents:

*******************
What the file holds
*******************

.. list-table::
    :header-rows: 1
    :widths: 22 78

    *   - Record
        - Contents

    *   - Schema
        - One per data type. The name is the DDS type name, the encoding is |br|
          ``omgidl``, and the data is the type rendered as IDL — empty when |br|
          the type was never described.

    *   - Channel
        - One per DDS Topic, named after the topic verbatim, with the |br|
          message encoding ``cdr``. Its metadata carries ``qos``, |br|
          ``ros2-types`` and ``partitions``.

    *   - Message
        - One per recorded sample. ``data`` is the serialized sample exactly |br|
          as it was sent, encapsulation header included; ``logTime`` is when |br|
          the sniffer captured the packet and ``publishTime`` when the |br|
          publishing participant sent it, both in nanoseconds.

    *   - Metadata
        - ``version`` identifies the tool that wrote the file. |br|
          ``messages_guid`` and ``messages_guid_index`` together identify the |br|
          publishing DataWriter of every message; see below.

A Channel is written for every topic the discovery traffic announced, including the topics that
never carried a sample, so the channel list is the full picture of what was on the network.

.. _user_manual_mcap_output_guid:

*****************************
Finding the publishing writer
*****************************

MCAP has no field for the :term:`Guid` of the DataWriter that published a message, so it is recovered
in two hops through the metadata records, which is what *DDS Record & Replay* does and therefore what
its tools expect:

#. ``messages_guid`` maps the ``sequence`` of a message to a small index.
#. ``messages_guid_index`` maps that index to the GUID string.

The indirection keeps the mapping compact when many messages share one writer.

.. note::

    ``Message.sequence`` is a single counter across the whole file, starting at zero — not the RTPS
    sequence number of the sample, and not a per-channel counter.
    It has to be file-wide because ``messages_guid`` is keyed by it alone, so a per-channel counter
    would let two channels collide in that map.

    This is a deliberate difference from the database output, where
    ``Messages.sequence_number`` **is** the RTPS sequence number.
    Converting an MCAP file recorded here into a database therefore yields a ``sequence_number``
    that differs from the one a ``-monitor`` run of the same capture produces, even though every
    other field matches.

.. _user_manual_mcap_output_duplicates:

**********
Duplicates
**********

A capture normally contains the same sample more than once, because it was seen both as multicast and
as unicast or because the writer repaired it.
Unlike the database, where the primary key removes them for free, the MCAP output recognizes
duplicates explicitly: a sample whose writer GUID and RTPS sequence number were already written is
skipped.

The result is that a capture yields the same number of MCAP messages as it yields rows in the
``Messages`` table of a ``-monitor`` recording, which makes the two outputs directly comparable.

.. _user_manual_mcap_output_limits:

*****************
What is not in it
*****************

* **No JSON view of the samples.** The payload is CDR; nothing decodes it while recording.
* **No serialized type objects.** *DDS Record & Replay* stores a ``DynamicTypesCollection``
  attachment holding base64 type objects, which the RTPS traffic does not carry. The IDL text in the
  Schema record is all the type information available.
* **No QoS and no partitions.** The ``qos`` channel metadata holds the *DDS Record & Replay*
  defaults and ``partitions`` is empty, because |eddsrecorder| extracts neither from the discovery
  traffic.
* **No splitting by size.** One capture produces one file, however large.

The chunks are compressed with Zstandard, which is the library default and is not configurable.

.. _user_manual_mcap_output_reading:

**********
Reading it
**********

Any MCAP reader can open the file.
The `mcap CLI <https://mcap.dev/guides/cli>`_ summarizes it without any type information:

.. code-block:: bash

    mcap info session.mcap
    mcap list channels session.mcap

To see the values inside the samples, open the file with *eProsima DDS Monitor*.
