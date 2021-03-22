#! /usr/bin/env bash

# This script will apply make to the Makefile to compile an executable in the build dir

echo "Building Cmake..."

cd ..
[ ! -d ./build ] && echo "Build directory does not exist... Exiting." && exit 1
cmake --configure --build ./build
