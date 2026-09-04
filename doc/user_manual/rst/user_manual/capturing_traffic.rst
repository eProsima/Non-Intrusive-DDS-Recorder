.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_capturing_traffic:

#####################
Capturing DDS traffic
#####################

|eddsrecorder| processes a capture file; it does not produce one.
The quality of the recording therefore depends entirely on how the capture was taken, and a capture that looks fine in
a protocol analyzer may still be unusable here.
This section describes what |eddsrecorder| expects from a capture file and how to obtain one.

.. _user_manual_capturing_traffic_requirements:

**********************
What the capture needs
**********************

.. list-table::
    :header-rows: 1
    :widths: 26 74

    *   - Requirement
        - Why

    *   - Complete packets
        - |eddsrecorder| discards every packet whose captured length differs |br|
          from its length on the wire, so a capture taken with a reduced |br|
          snapshot length yields an empty or incomplete database.

    *   - The discovery phase
        - The data type schema and the topic-to-endpoint mapping are learned |br|
          from the discovery traffic. A capture started after the applications |br|
          have discovered each other contains user samples that |br|
          |eddsrecorder| cannot interpret.

    *   - A supported link layer
        - Ethernet, loopback, Linux cooked capture (the ``any`` |br|
          interface) and raw IP are understood. |br|
          Any other link layer is reported when the file is opened. |br|
          See :ref:`user_manual_limitations_link_layers`.

    *   - IPv4 and UDP
        - RTPS over UDP/IPv4 is dissected. Traffic over IPv6 or TCP is not |br|
          recognized.

    *   - Unencrypted RTPS
        - The dissector reads the RTPS submessages directly, so traffic |br|
          protected with DDS Security cannot be decoded.

See :ref:`user_manual_limitations` for the complete list.

.. _user_manual_capturing_traffic_where:

****************
Where to capture
****************

A network interface in the default configuration only receives the traffic addressed to its own node, which for a DDS
system means the multicast discovery traffic plus the samples that this particular node has subscribed to.
That is enough to record a single application, but not a whole system.

To record every participant of a DDS network, capture on a **mirror port** of the switch, also known as the
:term:`switch debug port`, configured to duplicate the traffic of the ports where the DDS nodes are connected.

.. note::

    Discovery is largely multicast, while user samples are frequently sent unicast to each matched reader.
    A capture point that sees the multicast traffic but not the unicast traffic produces a database with populated
    ``Topics`` and ``Endpoints`` tables and no samples.

If all the applications run on the same host, capture on the loopback interface instead: ``lo`` on Linux, ``lo0`` on
macOS and the BSDs, and the loopback adapter provided by *Npcap* on Windows.

When the participants are spread over several interfaces of the same host, or you are not sure which interface carries
the traffic, capture on the Linux ``any`` pseudo-interface, which records every interface at once:

.. code-block:: bash

    sudo tcpdump -i any -s 0 -w capture.pcap udp

|eddsrecorder| understands the *Linux cooked capture* link layer that ``any`` produces, in both its v1 and v2 forms, as
well as the loopback link layers of every supported platform.
:ref:`user_manual_limitations_link_layers` lists them all.

.. note::

    A capture taken on ``any`` contains the same packet more than once when it crosses two captured interfaces, and
    loopback traffic is normally seen twice, once on transmission and once on reception.
    Both show up as repeated samples in the database; :ref:`user_manual_querying_database` shows how to detect them.

.. _user_manual_capturing_traffic_wireshark:

************************
Capturing with Wireshark
************************

In the *Capture Options* dialog:

#. Select the interface connected to the switch mirror port.
#. Leave the **snapshot length** at its default (*default* means unlimited).
   Do **not** set a limited value: a truncated capture is rejected packet by packet.
#. Optionally set a capture filter to keep the file small, for example ``udp``.
#. Start the capture, then start the DDS applications, so that the discovery phase is included.
#. Stop the capture and save the file.

Both the classic ``pcap`` format and the ``pcapng`` format that Wireshark writes by default are accepted.
If a file is ever rejected, convert it with:

.. code-block:: bash

    editcap -F pcap capture.pcapng capture.pcap

.. _user_manual_capturing_traffic_cli:

**********************
Capturing from the CLI
**********************

The same capture can be taken without a graphical interface.
With ``tcpdump``, the ``-s 0`` flag requests full packets and ``-w`` writes the classic ``pcap`` format:

.. code-block:: bash

    sudo tcpdump -i eth0 -s 0 -w capture.pcap udp

The equivalent with ``tshark`` is:

.. code-block:: bash

    sudo tshark -i eth0 -s 0 -w capture.pcap udp

To restrict the capture to a single DDS domain, filter by the port range that the domain uses.
The RTPS ports derive from the :term:`Domain Id`, so the simplest reliable approach is to capture all UDP traffic and
let |eddsrecorder| ignore whatever is not RTPS.

.. _user_manual_capturing_traffic_checking:

***********************
Checking a capture file
***********************

Before recording a long capture, confirm that it contains what you expect.
Wireshark decodes RTPS out of the box, so the display filter ``rtps`` shows the RTPS packets in the file, and
``rtps.sm.id == 0x15`` narrows it down to the ``DATA`` submessages that carry discovery announcements and user samples.

The equivalent check from the command line is:

.. code-block:: bash

    tshark -r capture.pcap -Y rtps -T fields -e frame.number -e rtps.sm.id | head

Finally, run |eddsrecorder| itself: the ``Number of processed RTPS packets`` line it prints is the number of packets it
was able to recognize, and it is the fastest way to tell a capture problem from a recording problem.
