#!/usr/bin/env bash

set -e
set -o pipefail

# Script to construct a python wrapper around the C++ code using SWIG.
# SWIG configuration resides in `<repo_root>/eCP/swig/``.
# This code is called inside docker image when built alongside other 
# algorithms in the ann-benchmarks repo.

# This script creates a `<repo_root>/eCP/build/` dir and asks Cmake to build inside.
# Currently .so and .py can be found both in: '<repo_root>/eCP/build/swig/'.

# Dependencies: cmake

NAME="gen_wrapper"

echo "${NAME}: Setting up python 3.6 env..."
cd ..		# root ecp dir
python3.6 -m venv env
source env/bin/activate

echo "${NAME}: Compiling project incl SWIG generated shared library..."
cd eCP/
[ ! -d build ] \
&& echo "${NAME}: Creating build dir..." \
&& mkdir build

echo "${NAME}: Configuring Cmake..."
cmake -S . -B build

echo "${NAME}: Building Cmake..."
cmake --configure build # is currently necessary on ubuntu docker image
cmake --build build

echo "${NAME}: Wrapper generation successful."