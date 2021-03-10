#!/usr/bin/env bash

set -e
set -o pipefail

# Script to construct a python wrapper around the C++ code using SWIG.
# This code is called inside docker image when built alongside other 
# algorithms in the ann-benchmarks repo.
# Currently .so and .py can be found both in: '<eCP_root>/eCP/build/swig/'

# Dependencies: cmake

NAME="gen_wrapper"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

echo "${NAME}: Setting up python 3.6 env..."
cd ..		# root ecp dir
python3.6 -m venv env
source env/bin/activate

echo "1: "
pwd
echo ""

echo "${NAME}: Compiling project incl SWIG generated shared library..."
cd eCP/

echo "2: "
pwd
echo ""

[ ! -d build ] \
&& echo "${NAME}: Creating build dir..." \
&& mkdir build

echo "${NAME}: Configuring Cmake..."
cmake -S . -B build

echo "3: "
pwd
echo ""

echo "${NAME}: Building Cmake..."
cmake --configure build
cmake --build build

# ./configure.sh
# ./build.sh

echo "${NAME}: Wrapper generation successful."

# Generate python wrapper
#cd ../	# eCP C++ dir
#cp swig/setup.py build/swig
#cd swig
#python3 setup.py build_ext --inplace && echo "Wrapper generated OK."