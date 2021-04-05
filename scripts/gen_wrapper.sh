#!/usr/bin/env bash

set -e
set -o pipefail

# This script is called from the 'Dockerfile.ecp' docker image, when ann-benchmarks 
# installs ecp into the framework.

# The script creates a `<eCP_root>/eCP/build/` dir and asks CMake to build the
# C++ source code + the SWIG wrapper as Release build inside inside that directory.

# SWIG configuration is found in `<eCP_root>/eCP/swig/``.
# Python wrapper is found in: '<eCP_root>/eCP/build/swig/' and consist of a 
# shared library '_eCP_wrapper.so' and a Python-based wrapper 'eCP_wrapper.py'.

# Dependencies: cmake3.8 <, swig3.6 <

NAME="gen_wrapper"

echo "${NAME}: Compiling project incl SWIG-generated shared library..."
cd ../eCP/scripts

echo "${NAME}: Configuring Cmake..."
chmod +x configure.sh
./configure.sh Release

echo "${NAME}: Building Cmake..."
chmod +x build.sh
./build.sh

echo "${NAME}: Wrapper generation successful."
