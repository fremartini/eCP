#! /usr/bin/env bash

# This script will configure cmake meaning generate make files in build dir

echo "Configuring Cmake..."

cd ..
[ ! -d ./build ] && echo "Creating build directory..." && mkdir ./build
cmake -S ./ -B ./build
