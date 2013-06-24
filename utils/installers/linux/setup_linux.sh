#!/bin/sh

# This scripts creates a tar.gz file with all the linux installation in 64

project="DDSRecorder"
version=$1

function installer
{
	# Copy documentation.
	mkdir -p tmp/$project/doc
	cp "../../../doc/Installation Manual.pdf" tmp/$project/doc
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	cp "../../../doc/Users Manual.pdf" tmp/$project/doc
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy example.
	mkdir -p tmp/$project/examples
	mkdir -p tmp/$project/examples/HelloWorld
	cp ../../../examples/HelloWorld/HelloWorld.pcap tmp/$project/examples/HelloWorld
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	cp ../../../examples/HelloWorld/HelloWorld.db tmp/$project/examples/HelloWorld
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy licenses.
	cp ../../../doc/licencias/DDSRECORDER_LICENSE.txt tmp/$project
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	cp ../../../doc/licencias/LGPLv3_LICENSE.txt tmp/$project
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	mkdir -p tmp/$project/bin
	cp ../../../lib/$EPROSIMA_TARGET/DDSRecorder tmp/$project/bin
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	cd tmp
	tar cvzf "../${project}_${version}_Fedora17_${EPROSIMA_TARGET:0:3}.tar.gz" $project
	errorstatus=$?
	cd ..
	if [ $errorstatus != 0 ]; then return; fi
}

if [ -z $1 ]; then
	echo "Needs as parameter the version of the product $project"
	exit -1
fi

# Create the temporaly directory.
mkdir tmp
mkdir tmp/$project

installer

# Remove temporaly directory
rm -rf tmp

if [ $errorstatus == 0 ]; then
    echo "INSTALLER SUCCESSFULLY"
else
    echo "INSTALLER FAILED"
fi

exit $errorstatus
