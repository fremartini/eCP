#! /usr/bin/env bash

# This script will configure cmake meaning generate make files in build dir

# cmake -DCMAKE_BUILD_TYPE=Debug -S ../ -B ../build
echo "Configuring Cmake..."

cd ..
[ ! -d ./build ] && echo "Creating build directory..." && mkdir ./build
cmake -S ./ -B ./build
