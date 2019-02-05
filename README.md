# eProsima Non-Intrusive DDS Recorder
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

<a href="http://www.eprosima.com"><img src="https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ" align="left" hspace="8" vspace="2" width="100" height="100" ></a>
*eProsima Non-Intrusive DDS Recorder* is a tool to record all the DDS traffic in your network, using a non-intrusive
mechanism allowing you to test, analyze or log your DDS distributed system without adding any new DDS participant or
service, ensuring you are recording the real behavior and timing.

## How it works

*eProsima Non-Intrusive DDS Recorder* records the DDS traffic sniffing the DDS protocol (RTPS) through the switch debug
port.
The tool dissects the protocol and builds a complete database of all the DDS entities (Participants, Publishers,
Subscribers, and Topics), the Data Types, and all the exchanged messages.

*eProsima Non-Intrusive DDS Recorder* does not record just raw data: it builds a message table for each DDS Topic, with
the same fields as the corresponding DDS Topic Data Type.

In this release you need a sniffer such as wireshark to save the network traffic into a standard packet capture file
(PCAP).
*eProsima Non-Intrusive DDS Recorder* will later parse  the file to translate the RTPS messages into a human readable
format and store them in a SQLite database.
In order to get all the traffic in your network you should sniff your switch debug port, otherwise you would get just
the traffic directed to the node where the sniffer is running.
Future releases will include a built-in sniffer to process the network packets in real time.

DDS uses an automatic discovery process to discover all the DDS entities in your network including your topic data
types.
*eProsima Non-Intrusive DDS Recorder* analyzes the discovery traffic to build a set of tables in a database using your
data types schema to store the DDS user data traffic later.

To get the data type information *eProsima Non-Intrusive DDS Recorder* searchs for the data type definition ( Typecode)
in the discovery messages.
It is important to note that not all the available DDS implementations send the typecode information (see supported DDS
implementations in the release notes).
Future releases of *eProsima Non-Intrusive DDS Recorder* will allow the use of an IDL file to generate the typecode of
your types.

# #Usage

*eProsima Non-Intrusive DDS Recorder* is a command line application.
The command line syntax is:

```bash
DDSRecorder <pcap_file> [-db <database>] [-tcMaxSize <size>] [-idl <file>] [-help]
```

* *< pcap_file >*: name of the file that the application will analyze.
This file should be a PCAP format.
* *-db < database >*: name of the SQLite file that will be created and used to store the translated RTPS messages.
By default *eProsima Non-Intrusive DDS Recorder* creates the file `dump.db`.
* *-tcMaxSize < size >*: TypeCode maximum allowed size (Default: 2048)
* *-idl < file >*: IDL file containing all data types used in the captured system if their typecodes are not being sent
in the discovery phase.
* *-help*: Print help information.

## Available documentation

* [**User Manual (PDF)**](https://www.eprosima.com/docs/non-intrusive-dds-recorder/1.0.0/pdf/User-Manual.pdf)
* [**Installation Manual (PDF)**](https://www.eprosima.com/docs/non-intrusive-dds-recorder/1.0.0/pdf/Installation-Manual.pdf)
* [**Release Notes (PDF)**](https://www.eprosima.com/docs/non-intrusive-dds-recorder/1.0.0/pdf/Release-Notes.pdf)
