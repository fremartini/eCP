#!/bin/bash

#this script should only be run as root
if [ "$EUID" -ne 0 ]
    then echo "Please run as root"
    exit
fi

#if no arguments are supplied, display help
if [[ $# -eq 0 ]]; then
    echo -e "usage: sudo ./run.sh [commit,name,dataset,earlyhalt]"
    exit
fi

echo -e "running $# experiment(s)"

cd ..

#if the ann-benchmarks repository already exists, we dont have to clone it
if [ ! -d ann-benchmarks ]
then
    echo "cloning new ann-benchmarks repository"
    git clone https://github.com/erikbern/ann-benchmarks.git
    chmod 777 ann-benchmarks -R
else
    echo "using existing ann-benchmarks repository"
fi


for experiment in "$@"
do
    CLEAN_STR=$(echo $experiment | tr -d '[]')
    SPLIT=(${CLEAN_STR//,/ })

    if [[ ${#SPLIT[@]} -ne 4 ]]; then
        echo -e "malformed experiment: ${SPLIT[@]}, expected 4 arguments got ${#SPLIT[@]}"
    fi

    COMMIT_ID=${SPLIT[0]}
    NAME=${SPLIT[1]}
    DATASET=${SPLIT[2]}
    HALT=${SPLIT[3]}

    echo -e "RUNNING EXPERIMENT WITH FOLLOWING CONFIGURATION:"
    echo -e "COMMIT_ID: $COMMIT_ID"
    echo -e "NAME:      $NAME"
    echo -e "DATASET:   $DATASET"
    echo -e "HALT:      $HALT"

    #move files from benchmarks-files into ann-benchmarks
    #rm ann-benchmarks/install/Dockerfile.*
    cp benchmarks-files/eCP.py 		    ann-benchmarks/ann_benchmarks/algorithms/eCP.py
    cp benchmarks-files/Dockerfile.ecp 	ann-benchmarks/install/Dockerfile.ecp
    cp benchmarks-files/algos.yaml		ann-benchmarks/algos.yaml
    cd ann-benchmarks

    #replace strings in eCP dockerfile and algos.yaml to determine what experiments are run
    sed -i "s/#ECP_COMMIT/RUN git checkout $COMMIT_ID/" "install/Dockerfile.ecp"
    sed -i "s/%ECP_NAME%/$NAME/" "algos.yaml"
    sed -i "s/%ECP_EA%/$HALT/" "algos.yaml"

    #remove docker image if exists to prevent failures caused by old images
    if [ $(docker images -q ann-benchmarks-ecp) ]
    then
        docker rmi ann-benchmarks-ecp:latest --force
    fi

    python3.6 install.py --algorithm ecp
    python3.6 run.py --algorithm $NAME --dataset $DATASET

    cd ..
done

cd ann-benchmarks

if [ ! -d website ]; then
    mkdir website
fi

python3.6 create_website.py --outputdir website/

chmod 777 -R ./
