#! /usr/bin/env bash

# Script to install eCP algorithm into ann-benchmarks. It is assumed that 
# the 'ann-benchmarks' and the 'eCP' repositories are located in the same 
# dir './' and that this script is called from './eCP.'.
# It is also assumed that python 3.6 is used eg. using venv.
#
# Example:
# ./ 
#   ann-benchmarks/
#   eCp/

cd ..

[ ! -d ann-benchmarks ] && echo "Clone new repo" && git clone https://github.com/mortenskoett/ann-benchmarks/

echo "Copy eCP necessary files"
cp -r eCP/ann-benchmarks/* ann-benchmarks/

echo "Setup python 3.6 env"
cd ann-benchmarks
source env/bin/activate

echo "Install dependencies"
pip install -r requirements.txt

echo "Building docker images"
sudo python install.py --algorithm ecp

echo "Run test on random-xs-20-euclidean"
sudo python run.py --algorithm eCP --dataset random-xs-20-euclidean
sudo python plot.py --dataset random-xs-20-euclidean

