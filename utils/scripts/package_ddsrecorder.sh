#!/bin/sh

#: This script pack DDSRecorder library for any platform in Linux.
#
# To compile DDSRecorder is needed to install libpcap-devel and sqlite-devel packages.
#    Example in Fedora: yum install libpcap-devel sqlite-devel
#
# This script needs the next programs to be run.
# - subversion
# - libreoffice
# Also this script needs the eProsima.documentation.changeVersion macro installed in the system.

errorstatus=0

# Default value, oll platforms will be generated (i86, x64)
package_targets=""

function package
{
    cd thirdparty/fastcdr
    # Get the current version of CDR
    . ../dev-env/scripts/common_pack_functions.sh getVersionFromCPP cdrversion include/fastcdr/FastCdr_version.h

    # Compile and packaging FastCDR library for all archictectures
    cd utils/scripts
    ./package_fastcdr.sh
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    cd ../../../..

    # Get the current version of DDSRecorder
    . thirdparty/dev-env/scripts/common_pack_functions.sh getVersionFromCPP recorderversion src/version.cpp
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi

    # Compile DDSRecorder application.
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # Compile DDSRecorder for target i86.
    if [ -z $package_targets ] || [ "$package_targets" == "i86" ]; then
        #Change EPROSIMA_TARGET
        EPROSIMA_TARGET="i86Linux2.6gcc"
        # Compile DDSRecorder for target.
        rm -rf output
        make
        errorstatus=$?
        if [ $errorstatus != 0 ]; then return; fi
    fi
    if [ -z $package_targets ] || [ "$package_targets" == "x64" ]; then
        #Change EPROSIMA_TARGET
        EPROSIMA_TARGET="x64Linux2.6gcc"
        # Compile DDSRecorder for target.
        rm -rf output
        make
        errorstatus=$?
        if [ $errorstatus != 0 ]; then return; fi
    fi

    # Create PDFS from documentation.
    cd doc
    # Installation manual
    soffice --headless "macro:///eProsima.documentation.changeVersion($PWD/Installation Manual.odt,$recorderversion)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # User manual
    soffice --headless "macro:///eProsima.documentation.changeVersion($PWD/User Manual.odt,$recorderversion)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # Release notes
    soffice --headless "macro:///eProsima.documentation.changeVersion($PWD/Release Notes.odt,$recorderversion)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    cd ..

    # Create README
    soffice --headless "macro:///eProsima.documentation.changeVersionToHTML($PWD/README.odt,$recorderversion)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi

    # Create installers
    cd utils/installers/linux
    ./setup_linux.sh $recorderversion
    cd ../../..
}

# Get the optional parameter
if [ $# -ge 1 ] && [ -n $1 ]; then
    if [ "$1" == "i86" ] || [ "$1" == "x64" ]; then
        package_targets=$1
    else
        echo Error: Bad argument. Valid values. i86, x64
        exit -1;
    fi
fi

# Go to root directory
cd ../..

package

if [ $errorstatus == 0 ]; then
    echo "PACKAGING SUCCESSFULLY"
else
    echo "PACKAGING FAILED"
fi

exit $errorstatus
