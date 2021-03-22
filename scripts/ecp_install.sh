#! /usr/bin/env bash

# Script to install and build eCP docker image with ann-benchmarks. It is assumed that 
# the 'ann-benchmarks' and the 'eCP' repositories are located in the same 
# dir './' and that this script is called from './eCP/scripts.
# It is also assumed that python 3.6 is used eg. using venv and that the remote contains the
# code as the ecp docker image will pull it down inside ann-benchmarks.

# Attention: It is necessary to set REPO_DIR_NAME variable to the name you have
# given the eCP repository.

# Example:
# ./ 
#   ann-benchmarks/
#   eCp/
#     scripts/

REPO_DIR_NAME="eCP"

echo "Will install eCP docker image into ann-benchmarks..."
read -p "Press enter to continue"

cd ../..

[ ! -d ann-benchmarks ] \
    && echo "Cloning new ann-benchmarks repo" \
    && git clone https://github.com/mortenskoett/ann-benchmarks/

echo "Copy eCP necessary files"
cp -r ${REPO_DIR_NAME}/ann-benchmarks/* ann-benchmarks/

echo "Setup python 3.6 env inside ann-benchmarks"
cd ann-benchmarks
python3.6 -m venv env
source env/bin/activate

echo "Install dependencies"
pip install -r requirements.txt

echo "Building ONLY eCP docker image"
python install.py --algorithm ecp
