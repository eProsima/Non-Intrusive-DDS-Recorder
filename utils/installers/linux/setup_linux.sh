#!/bin/sh

# This scripts creates a tar.gz file with all the linux installation.
# @param The version of the project

# To create the source tar file you have to install next packages:
# autoconf, automake, libtool

project="DDSRecorder"

function installer
{
	# Copy licenses.
	cp ../../../doc/licencias/DDSRECORDER_LICENSE.txt tmp/$project
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	cp ../../../doc/licencias/LGPLv3_LICENSE.txt tmp/$project
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy documentation.
	mkdir -p tmp/$project/doc
	# Installation Manual
	cp "../../../doc/Installation Manual.pdf" tmp/$project/doc
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	# User Manual
	cp "../../../doc/User Manual.pdf" tmp/$project/doc
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	# Release Notes
	cp "../../../doc/Release Notes.pdf" tmp/$project/doc
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
	cp ../../../examples/HelloWorld/HelloWorld.idl tmp/$project/examples/HelloWorld
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy Readme
	cp ../../../README.html tmp/$project/doc

	# Copy DDSRecorder headers
	mkdir -p tmp/$project/include
	cp -r ../../../include/* tmp/$project/include
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy eProsima header files
	mkdir -p tmp/$project/include/eProsima_c/macros
	cp ../../../thirdparty/eprosima-common-code/eProsima_c/macros/snprintf.h tmp/$project/include/eProsima_c/macros
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy DDSRecorder sources
	mkdir -p tmp/$project/src
	cp -r ../../../src/* tmp/$project/src
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Copy autoconf configuration files.
	cp configure.ac tmp/$project
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	cp Makefile.am tmp/$project
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi

	# Generate autoconf files
	cd tmp/$project
	sed -i "s/VERSION/${version}/g" configure.ac
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	sed -i "s/VERSION_MAJOR/`echo ${version} | cut -d. -f1`/g" Makefile.am
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	sed -i "s/VERSION_MINOR/`echo ${version} | cut -d. -f2`/g" Makefile.am
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	sed -i "s/VERSION_RELEASE/`echo ${version} | cut -d. -f3`/g" Makefile.am
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	autoreconf --force --install
	errorstatus=$?
	if [ $errorstatus != 0 ]; then return; fi
	cd ../..

	cd tmp
	tar cvzf "../${project}_${version}_${distroversion}.tar.gz" $project
	errorstatus=$?
	cd ..
	if [ $errorstatus != 0 ]; then return; fi
}

if [ -z $1 ]; then
	echo "Needs as parameter the version of the product $project"
	exit -1
fi

version=$1

# Get distro version
. ../../../thirdparty/dev-env/scripts/common_pack_functions.sh getDistroVersion

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
