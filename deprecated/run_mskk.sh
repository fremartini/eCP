#! /usr/bin/env bash

# Script to run eCP algorithm using ann-benchmarks
# It is assumed that the the 'ann-benchmarks' and the 'eCp'
# repositories are located in the same dir './' and this script
# called from './eCP.'
#
# Example:
# ./ 
#   ann-benchmarks/
#   eCp/

ANN=ann-benchmarks
ECP=eCP

echo "Moving to parent dir containing both repos"
cd ..

echo "Setting permission on ann-benchmarks dir"
sudo chmod -R 777 $ANN

if [ -z "$1" ] && [ "$1" = "all" ]; then  # if arg1 empty
    echo "Moving non-eCP algorithms"
    mkdir -p $ANN/bak_install
    mv $ANN/install/Dockerfile.* $ANN/bak_install
else
    echo "Reinsterting non-eCP algorithms"
    mv $ANN/bak_install/* $ANN/install
fi

echo "Copying necessary eCp files to ann-benchmarks repo"
cp -r $ECP/ann-benchmarks/* $ANN/

echo "Setup python 3.6 env"
cd $ANN
source env/bin/activate

echo "Running test on random-xs-20-euclidean"
if [ ! -z "$1" ] && [ "$1" = "all" ]; then
    echo "Running all"
    python install.py
    sudo python run.py --dataset random-xs-20-euclidean
else
    echo "Running eCP only"
    python install.py --algorithm ecp
    sudo python run.py --algorithm eCP --dataset random-xs-20-euclidean
fi

sudo chmod -R 777 ./
sudo python plot.py --dataset random-xs-20-euclidean