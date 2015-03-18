eProsima Non-Intrusive DDS Recorder installation requires the following steps:

1. eProsima Non-Intrusive DDS Recorder requires the installation of eProsima FastCDR library on
your system. eProsima FastCDR library is provided under the folder
"requiredcomponents". Extract the content of the package
"fastcdr_1.0.1.tar.gz" and execute:

    For 32-bit machines
    $ cd fastcdr; ./configure --libdir=/usr/lib; make; make install

    For 64-bit machines
    $ cd fastcdr; ./configure --libdir=/usr/lib64; make; make install

2. eProsima Non-Intrusive DDS Recorder also requires Boost libraries. Install them using your
Linux distribution package manager.

3. Install the eProsima Non-Intrusive DDS Recorder software.

    $ cd DDSRecorder; ./configure; make; make install

For more information read the Installation manual located in
"DDSRecorder/doc/pdf/Installation Manual.pdf"
