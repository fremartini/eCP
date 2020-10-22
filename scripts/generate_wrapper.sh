#!/usr/bin/env bash

# Script to construct a python wrapper around the C++ code using SWIG.
# This code is called inside docker image when built alongside other 
# algorithms in the ann-benchmarks repo.

# Root is relative to where script is located
ROOT=".."
ECP="${ROOT}/eCP"
SRC="${ECP}/src"
HEADERS="${ECP}/include/eCP"
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

# Combine source code and headers into each a single file
combine \
    ${SRC}/eCP.cpp \
    ${SRC}/distance.cpp \
    ${SRC}/pre-processing.cpp \
    ${SRC}/query-processing.cpp \
    --out ${GEN_FILES}/combined.cpp && echo "Src generated OK."

combine \
    ${HEADERS}/data_structure.hpp \
    ${HEADERS}/eCP.hpp \
    ${HEADERS}/pre-processing.hpp \
    ${HEADERS}/query-processing.hpp \
    --out ${GEN_FILES}/combined.hpp && echo "Headers generated OK."

# Setup python 3.6 env
python3.6 -m venv ${ROOT}/env
source ${ROOT}/env/bin/activate

# Generate wrapper using SWIG
python3 ${WRAPPER}/interface_gen.py \
    --file ${GEN_FILES}/combined.cpp \
    --out ${GEN_FILES} && echo "interface_gen.py ran OK."

swig -c++ -python ${GEN_FILES}/eCP.i && echo "swig ran OK."

cd ${GEN_FILES}
python3 ../setup.py build_ext --inplace && echo "Wrapper generated OK."