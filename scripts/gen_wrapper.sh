#!/usr/bin/env bash

set -e
set -o pipefail

# This script is called from the 'Dockerfile.ecp' docker image, when ann-benchmarks 
# installs ecp into the framework.

# The script creates a `<eCP_root>/eCP/build/` dir and asks CMake to build the
# C++ source code + the SWIG wrapper inside inside that directory.

# SWIG configuration is found in `<eCP_root>/eCP/swig/``.
# Python wrapper is found in: '<eCP_root>/eCP/build/swig/' and consist of a 
# shared library '_eCP_wrapper.so' and a Python-based wrapper 'eCP_wrapper.py'.

# Dependencies: cmake3.8 <, swig3.6 <

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
