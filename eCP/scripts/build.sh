#! /usr/bin/env bash

# This script will apply make to the Makefile to compile an executable in the build dir

#cmake --build ../build --config Debug
#cmake --build ../build -- VERBOSE=1

echo "Building Cmake..."

cd ..
[ ! -d ./build ] && echo "Creating build directory..." && mkdir ./build
cmake --configure --build ./build
