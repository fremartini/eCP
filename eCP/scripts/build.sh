#! /usr/bin/env bash

# This script will build a configured CMake project using Make. It expects a
# build dir to exist one level up in the directory structure.

echo "Building Cmake..."
[ ! -d ../build ] && echo "Build directory does not exist... Exiting." && exit 1
cd ../build
cmake --build ./ --target all
