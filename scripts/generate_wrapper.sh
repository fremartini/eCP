#!/usr/bin/env bash

set -e
set -o pipefail

# Script to construct a python wrapper around the C++ code using SWIG.
# This code is called inside docker image when built alongside other 
# algorithms in the ann-benchmarks repo.

# Root of project relative to where script is located
ROOT=".."
ECP="${ROOT}/eCP"
SRC_DIR="${ECP}/src"
HEADERS_DIR="${ECP}/include/eCP"
WRAPPER="${ROOT}/wrapper"
GEN_FILES="${WRAPPER}/files_generated"

# Convenience function to call combine script
combine() {
    python3 ${WRAPPER}/file_combine.py --files $@
}

# Create dir to store generated files
if [ ! -d "${GEN_FILES}" ]; then
    mkdir -p "${GEN_FILES}"
fi

# Collect src and header files
SOURCES=("$SRC_DIR"/*.cpp)
HEADERS=("$HEADERS_DIR"/*.hpp)

# Combine source code and headers into each a single file
combine ${SOURCES[@]} --out ${GEN_FILES}/combined.cpp && echo "Src generated OK."
combine ${HEADERS[@]} --out ${GEN_FILES}/combined.hpp && echo "Headers generated OK."

# Setup python 3.6 env
python3.6 -m venv ${ROOT}/env
source ${ROOT}/env/bin/activate

# Generate interface file -- deprecated
#  python3 ${WRAPPER}/interface_gen.py \
#      --file ${GEN_FILES}/combined.cpp \
#      --out ${GEN_FILES} && echo "interface_gen.py ran OK."

# Generate intermediate code using SWIG
cp ${WRAPPER}/eCP.i ${GEN_FILES}
swig -c++ -python ${GEN_FILES}/eCP.i && echo "swig ran OK."

# Generate python wrapper
cd ${GEN_FILES}
python3 ../setup.py build_ext --inplace && echo "Wrapper generated OK."