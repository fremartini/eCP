#! /usr/bin/env bash

# Script to install eCP algorithm into ann-benchmarks and build ONLY eCP. It is assumed that 
# the 'ann-benchmarks' and the 'eCP' repositories are located in the same 
# dir './' and that this script is called from './eCP.
# It is also assumed that python 3.6 is used eg. using venv and that the remote contains the
# code as the ecp docker image will pull it down inside ann-benchmarks.
#
# Example:
# ./ 
#   ann-benchmarks/
#   eCp/
#     scripts/

REPO_DIR_NAME="dynamic_eCP"
DATASET="random-xs-20-euclidean"

echo "Will install eCP docker-image into ann-benchmarks..."
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

# echo "Run test on ${DATASET}"
# python run.py --algorithm eCP --dataset ${DATASET}
# sudo python plot.py --dataset ${DATASET}