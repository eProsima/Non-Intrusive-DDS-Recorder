#!/bin/sh

#: This script pack DDSRecorder library for any platform in Linux.
#
# This script needs the next programs to be run.
# - subversion
# - libreoffice
# Also this script needs the eProsima.documentation.changeVersion macro installed in the system.

errorstatus=0

source $EPROSIMADIR/scripts/common_pack_functions.sh

function package
{
    # Get current version of GCC.
    getGccVersion

	# Get the initials of the target.
	getTargetFromEprosimaTarget

	#Change EPROSIMA_TARGET
	EPROSIMA_TARGET="${etarget}Linux2.6gcc${gccversion}"

    # Update and compile CDR library.
    cd ../CDR
    # Update CDR library.
    svn update
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # Compile CDR library for target.
    rm -rf output
    make
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    cd ../DDSRecorder

    # Get the current version of DDSRecorder
    getVersionFromCPP

    # Update and compile DDSRecorder application.
    # Update DDSRecorder application
    svn update
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # Compile DDSRecorder for target.
    rm -rf output
    make
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi

    # Create PDFS from documentation.
    cd doc
    # Installation manual
    soffice --headless "macro:///eProsima.documentation.changeVersion($PWD/Installation Manual.odt,$version)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # User manual
    soffice --headless "macro:///eProsima.documentation.changeVersion($PWD/User Manual.odt,$version)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    # Release notes
    soffice --headless "macro:///eProsima.documentation.changeVersion($PWD/Release Notes.odt,$version)"
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    cd ..

    # Create installers
    cd utils/installers/linux
    ./setup_linux.sh $version
    errorstatus=$?
    if [ $errorstatus != 0 ]; then return; fi
    cd ../../..
}

# Check that the environment.sh script was run.
if [ "$EPROSIMADIR" == "" ]; then
    echo "environment.sh must to be run."
    exit -1
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
