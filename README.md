[![Non-Intrusive DDS
Recorder](doc/resources/images/github_banner_ni_ddsrecorder.png)](https://eprosima.com/middleware/tools/non-intrusive-dds-recorder)

<br>

<div class="menu" align="center">
    <strong>
        <a href="https://eprosima.com/index.php/downloads-all">Download</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="https://non-intrusive-dds-recorder.readthedocs.io/en/latest/">Docs</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="https://eprosima.com/index.php/company-all/news">News</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="https://x.com/EProsima">X</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="mailto:info@eprosima.com">Contact Us</a>
    </strong>
</div>

<div class="badges" align="center">
    <a href="https://opensource.org/licenses/Apache-2.0"><img alt="License" src="https://img.shields.io/github/license/eProsima/Non-Intrusive-DDS-Recorder.svg"/></a>
    <a href="https://github.com/eProsima/Non-Intrusive-DDS-Recorder/releases"><img alt="Releases" src="https://img.shields.io/github/v/release/eProsima/Non-Intrusive-DDS-Recorder?sort=semver"/></a>
    <a href="https://github.com/eProsima/Non-Intrusive-DDS-Recorder/issues"><img alt="Issues" src="https://img.shields.io/github/issues/eProsima/Non-Intrusive-DDS-Recorder.svg"/></a>
    <a href="https://github.com/eProsima/Non-Intrusive-DDS-Recorder/network/members"><img alt="Forks" src="https://img.shields.io/github/forks/eProsima/Non-Intrusive-DDS-Recorder.svg"/></a>
    <a href="https://github.com/eProsima/Non-Intrusive-DDS-Recorder/stargazers"><img alt="Stars" src="https://img.shields.io/github/stars/eProsima/Non-Intrusive-DDS-Recorder.svg"/></a>
    <br>
    <a href="https://non-intrusive-dds-recorder.readthedocs.io"><img alt="Documentation badge" src="https://img.shields.io/readthedocs/non-intrusive-dds-recorder.svg"/></a>
</div>

*eProsima Non-Intrusive DDS Recorder* is a tool to record all the DDS traffic in your network, using a non-intrusive
mechanism allowing you to test, analyze or log your DDS distributed system without adding any new DDS participant or
service, ensuring you are recording the real behavior and timing.

## Commercial support

Looking for commercial support? Write us to info@eprosima.com

Find more about us at [eProsima’s webpage](https://eprosima.com/).

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

## Usage

*eProsima Non-Intrusive DDS Recorder* is a command line application.
The command line syntax is:

```bash
ni_ddsrecorder <pcap_file> [-db <database>] [-idl <file>] [-help]
```

* *< pcap_file >*: name of the file that the application will analyze.
This file should be a PCAP format.
* *-db < database >*: name of the SQLite file that will be created and used to store the translated RTPS messages.
By default *eProsima Non-Intrusive DDS Recorder* creates the file `dump.db`.
* *-idl < file >*: IDL file containing all data types used in the captured system if their typecodes are not being sent
in the discovery phase.
* *-help*: Print help information.

## Available documentation

* [**User Manual**](https://non-intrusive-dds-recorder.readthedocs.io/en/latest/rst/user_manual/introduction.html#user-manual-introduction)
* [**Installation Manual**](https://non-intrusive-dds-recorder.readthedocs.io/en/latest/rst/installation/requirements.html#installation-manual-requirements)
* [**Release Notes**](https://non-intrusive-dds-recorder.readthedocs.io/en/latest/rst/notes/notes.html#notes)
