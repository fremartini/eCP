#!/bin/bash

#this script should only be run as root
if [ "$EUID" -ne 0 ]
    then echo "Please run as root"
    exit
fi

#if no arguments are supplied, display help
if [[ $# -eq 0 ]]; then
    echo -e "usage: sudo ./run.sh [commit,name,dataset,earlyhalt]"
    echo -e "flags:"
    echo -e "-d | --delete | deletes ann-benchmarks folder if exists"
    echo -e "-l | --local  | runs ann-benchmarks locally"
    exit
fi

cd ..

DELETE_FLAG=false
LOCAL_FLAG=false

#look for arguments
for arg in "$@"
do
    if [[ $arg == "-d" || $arg == "--delete" ]]; then
         DELETE_FLAG=true
	 continue
    elif [[ $arg == "-l" || $arg == "--local" ]]; then
	 LOCAL_FLAG=true
	 continue
    fi
done

if $DELETE_FLAG && [ -d ann-benchmarks ]; then
    rm -rf ann-benchmarks
fi

#if the ann-benchmarks repository already exists, we dont have to clone it
if [ ! -d ann-benchmarks ]
then
    echo "cloning new ann-benchmarks repository"
    git clone https://github.com/erikbern/ann-benchmarks.git
    chmod 777 ann-benchmarks -R
else
    echo "using existing ann-benchmarks repository"
fi

for arg in "$@"
do
    #ignore arguments
    if [[ $arg == "-d" || $arg == "--delete" || $arg == "-l" || $arg == "--local" ]]; then
	continue
    fi
    
    #split string
    CLEAN_STR=$(echo $arg | tr -d '[]')
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
    cp benchmarks-files/eCP.py 		    ann-benchmarks/ann_benchmarks/algorithms/eCP.py
    cp benchmarks-files/Dockerfile.ecp 	    ann-benchmarks/install/Dockerfile.ecp
    cp benchmarks-files/algos.yaml	    ann-benchmarks/algos.yaml
    
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
    
    if $LOCAL_FLAG; then
        #generate the wrapper and copy it into ann-benchmarks
	cd ../scripts
	./gen_wrapper.sh
	cd ../ann-benchmarks
	cp ../eCP/build/swig/_eCP_wrapper.so .
	cp ../eCP/build/swig/eCP_wrapper.py .

    	python3.6 run.py --algorithm $NAME --dataset $DATASET --local
    else
        python3.6 run.py --algorithm $NAME --dataset $DATASET
    fi
    
    cd ..
done

cd ann-benchmarks

if [ ! -d website ]; then
    mkdir website
fi

python3.6 create_website.py --outputdir website/

chmod 777 -R ./
