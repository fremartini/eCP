#! /usr/bin/env bash

# This script will configure CMake i.e. generate make files in build dir
# as well as setup a useful dir structure for qtcreator build dirs.

# The script takes one of the following arguments: {Debug, Release}.
# If no argument is given it defaults to Release.

BUILD_TYPE="Release"

echo "Checking for script input args... [Debug, Release]"
if [ "$#" -eq 0 ]
  then
    echo "No arguments supplied, continuing with ${BUILD_TYPE} build."
else 
	[ "$1" != "Debug" ] && [ "$1" != "Release" ] && echo "Not valid input argument." && exit 1
	BUILD_TYPE="$1"
fi

echo "Configuring Cmake..."
[ ! -d ../build ] && echo "Creating build directory..." && mkdir ../build

echo "Setting up build dirs for qtcreator..."
mkdir -p ../build/Debug
mkdir -p ../build/Release
mkdir -p ../build/Release_Debug
mkdir -p ../build/Release_MinSize

echo "Setting build type: ${BUILD_TYPE}"
cmake -S ../ -B ../build -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
