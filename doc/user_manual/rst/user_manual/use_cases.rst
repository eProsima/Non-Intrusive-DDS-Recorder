.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_use_cases:

#########
Use cases
#########

Most ways of looking inside a running DDS system involve joining it: a monitoring subscriber, a logging application, a
debug tool that creates its own :term:`DomainParticipant`.
That works well during development, but there are situations in which adding an entity to the domain is undesirable,
impractical or simply not allowed.
|eddsrecorder| exists for those situations: it reconstructs the session from the traffic itself, so the system under
study is never touched.

This section explains when that trade-off pays off, and when a different approach fits better.

.. _user_manual_use_cases_observer_effect:

*************************
Why non-intrusive matters
*************************

Attaching a subscriber to a DDS domain is not a passive act.
A new participant changes the very system it is meant to observe:

* **It triggers discovery.**
  The new participant announces itself and every existing participant exchanges :term:`SPDP` and :term:`SEDP` traffic
  with it, and re-evaluates its endpoint matching.

* **It makes publishers do more work.**
  Once a new :term:`DataReader` matches, the matched :term:`DataWriter`\ s must deliver samples to one more
  destination.
  With a reliable :term:`QoS` this also means keeping samples in history for the new reader and answering its
  acknowledgments, which can change timing for the readers that were already there.

* **It consumes bandwidth and CPU on the observed nodes.**
  The extra copies travel over the same network, and the serialization work happens in the publishing application.

None of these effects are usually large, but they are real, and they are exactly the kind of perturbation that makes a
timing-sensitive or intermittent problem impossible to pin down: the moment you attach the tool, the symptom changes.

|eddsrecorder| removes the observer from the equation.
The capture is taken by a network sniffer on a mirror port, the DDS nodes never learn that anyone is listening, and the
recording therefore shows the real behavior and timing of the system.

.. _user_manual_use_cases_when:

**************
When to use it
**************

Recording a production system
=============================

This is the case |eddsrecorder| was designed for.
A deployed system runs an agreed set of processes on an agreed set of hosts; adding a recorder to it may be forbidden
by the operator, may require a change control procedure, or may simply not be possible because the nodes are embedded
devices with no room for another process.

The capture is taken on the network instead, and nothing on the nodes changes.
The analysis then happens offline, on a different machine, at whatever pace the investigation needs.

Investigating intermittent or hard to reproduce failures
========================================================

A failure that happens once a day cannot be caught by attaching a debugger when it occurs, because by then the evidence
is gone.
Capturing continuously and keeping the recent capture files gives you the traffic that preceded the incident, and
|eddsrecorder| turns it into a database you can query after the fact.

See :term:`PCAP file rotation` for the usual way of keeping a bounded amount of capture on disk.

Diagnosing discovery and matching problems
==========================================

When a DataReader never receives anything, the question is where the chain broke: the writer never announced itself,
the announcement never reached the reader host, the two matched but no data followed, or the data was sent somewhere
else.

Because the discovery messages are recorded verbatim, the database answers this directly.
The ``DiscoveryMessages`` table shows which endpoint was announced, from which IP and to which IP, and the
``Endpoints`` table shows the resulting view of the system.
:ref:`user_manual_querying_database_entities` collects the queries.

Interoperability between DDS implementations
============================================

When two vendors are supposed to interoperate, the wire is the only neutral arbiter: it shows what was actually sent
rather than what each library believes it sent.

|eddsrecorder| records the topic name and the type name as announced by each side, so a mismatch in either becomes
visible in ``Topics`` and ``Endpoints``.
The ``idl`` column of ``Types`` holds the type definition in readable IDL, taken from the file given with ``-idl``.

Characterizing traffic and timing
=================================

Because every sample carries the sniffer timestamp, taken from a single clock for the whole capture, the database
supports questions that are awkward to answer from inside the applications:

* At what period is a topic actually being published, and how much does it vary?
* How many times does the same sample travel on the wire, and to how many destinations?
* Which participant is responsible for most of the traffic on a topic?

:ref:`user_manual_querying_database_samples` works through these queries against the example capture.

.. note::

    |eddsrecorder| stores one row per RTPS ``DATA`` submessage observed, not one row per value written by the
    application.
    That distinction is what makes the traffic questions above answerable, and it is worth keeping in mind when
    counting samples.

Producing evidence from a test run
==================================

A capture taken during a test campaign becomes, after recording, an ordinary SQL dataset: it can be archived next to
the test report, compared against the dataset of a previous run, or checked with assertions written in any language
that can open a SQLite file.

This is often more convenient than instrumenting the applications, because it requires no change to the software under
test and produces the same artifact regardless of which DDS implementation is used.

.. _user_manual_use_cases_alternatives:

*********************************
When another approach fits better
*********************************

Non-intrusive recording is not free: it gives up everything that is not visible on the network, and everything that
requires being part of the domain.
The table below states when it is the wrong tool, so that the choice is made before the capture rather than after it.

.. list-table::
    :header-rows: 1
    :widths: 34 66

    *   - Situation
        - Why non-intrusive recording does not help

    *   - You need to react while the |br|
          system is running.
        - |eddsrecorder| processes a capture file after the fact. |br|
          Live monitoring requires a tool that is part of the domain.

    *   - The samples are large.
        - Samples big enough to be fragmented by RTPS travel in |br|
          ``DATA_FRAG`` submessages, which are not recorded.

    *   - The traffic is protected with |br|
          DDS Security.
        - The payload is encrypted on the wire and cannot be decoded |br|
          without the keys.

    *   - The applications share a host and |br|
          use shared memory or |br|
          intra-process delivery.
        - That traffic never reaches the network, so no sniffer can |br|
          observe it. Forcing the UDP transport changes the system, |br|
          which defeats the purpose.

    *   - You need the QoS policies of |br|
          each endpoint.
        - Only the topic name, the type name and the |br|
          :term:`Guid` are extracted from the discovery |br|
          messages.

    *   - You cannot reach a capture point |br|
          that sees the traffic.
        - A sniffer on an ordinary node only observes the traffic |br|
          addressed to that node. |br|
          See :ref:`user_manual_capturing_traffic_where`.

:ref:`user_manual_limitations` describes each of these boundaries in full, together with the symptoms they produce in a
recording.

.. _user_manual_use_cases_workflow:

******************
A typical workflow
******************

Whatever the use case, the sequence is the same, and each step has its own section in this manual:

#. **Choose the capture point and configure the sniffer**, so that the traffic of interest is captured whole.
   See :ref:`user_manual_capturing_traffic`.

#. **Capture the discovery phase as well as the data.**
   Start the capture before the applications, since the data types are learned from the discovery traffic.

#. **Record the capture into a database** with |eddsrecorder|.
   See :ref:`user_manual_usage`.

#. **Query the database** to answer the question that motivated the recording.
   See :ref:`user_manual_querying_database`.
