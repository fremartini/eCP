# Extended Cluster-Pruning
The extended cluster-pruning algorithm is implemented in C++ and provides a python wrapper for usage within the [ANN-benchmarking tool](https://github.com/erikbern/ann-benchmarks/) to compare with other state of the art ANN algorithms. 

Initially proposed as a bachelors project at the IT-University of Copenhagen in spring 2020. This repository continues the work by building a dynamic extension of the algorithm ontop of the original implementation.

This project is currently a work in progress. See [CONTRIBUTING.md](CONTRIBUTING.md) on how to contribute.

## Project dependencies
```
gcc, c++, cmake, python3.6, swig, hdf5, docker
```

# How-to's
The following descriptions assumes some sort of Linux distribution even if the eCP source code will compile on e.g. Windows.
It is also assumed that `./` is the root of this repository.

## How to compile eCP
1. Install dependencies outlined above.

2. Afterwards, to configure and compile project load the `CMakeLists.txt` file in the root dir using your favorite IDE, OR go to `./eCP/scripts` and execute:
```
configure.sh
build.sh
```
This will build the project in Release mode. To change this see `configure.sh` script. Currently only GNU/GCC is known to be supported.

## How to run eCP in ANN-Benchmarks
### Running it manually
1. Go to `./ann_benchmarks/install/Dockerfile.ecp` and change the line describing what repository is cloned when the eCP docker container 
is build by Ann-Benchmarks (AB).
Make it point to the current working branch e.g. `git clone -b <branch_name> <url_to_repo> eCP`, where 'eCP will be local name of repo dir to help build scripts. 

2. Push your work to the designated branch.

3. Execute the script `./scipts/ecp_install.sh` which will pull down AB repository and copy the needed files into the newly cloned AB repository. 
Here the Python requirements will be installed and finally an AB install script will be called to 
setup the eCP algorithm with AB, i.e. build a Docker image containing a compiled executable of the code 
from the designated branch from earlier.

4. Goto AB directory and follow the guide to run tests found at `https://github.com/erikbern/ann-benchmarks`.

### Using the provided run script
From within the eCP/scripts folder run the ann-benchmark.sh script, it takes arbitrarily many arguments in a array-style format depending on the amount of experiments the user wants to run. An example configuration could be ```sudo ./ann-benchmark.sh [abc123,foo,random-xs-20-euclidean,false] [def456,bar,random-xs-20-euclidean,true]``` corresponding to running the code at commit id abc123 on the random-xs-20-euclidean dataset without early halting and naming it foo whereafter commit id def456 would be run on the same dataset with early halting enabled and under the name bar. Observe there cannot be any spaces after each comma.

It supports the following flags:
* -d (--delete) delete the current local ann-benchmarks repository if it exists
* -l (--local) run ann-benchmarks in local mode (`https://github.com/erikbern/ann-benchmarks`)

### Running local changes
TODO

# Documentation
## Wrapper interface
SWIG is used to construct the Python-based wrapper around the C++ code. SWIG is
handled by CMake which will recompile the wrapper every time the code base is
recompiled. This will also happen inside the docker container, when the code is
send to the Ann-Benchmarks framework for testing.

The wrapper interface is described in `./eCP/swig/eCP.i` and exposes two 
functions from the C++ source code as outlined below. The interface file is
used to describe exactly what part of the C++ code is exposed through the
Python API:

### eCP_Index(S, L, m)
Builds an index with the provided dataset.
Accepts three arguments:
- A dataset (nested list of data points)
- Integer determining how many levels the index should have
- Metric for comparing distance (1 - Angular distance, 0 - Euclidean distance)

### query(I, q, k, b)
Queries the given index.
Accepts four arguments:
- Index to be queried
- Query point
- Amount of nearest neighbors to return
- Amount of clusters to search

## Python code example of using the wrapper
```python
import eCP_wrapper as e
index = e.eCP_Index([[41, 67, 34, 0, 69, 24],[78, 58, 62, 64, 5, 45],[81, 27, 61, 91, 95, 42],[27, 36, 91, 4, 2, 53],[92, 82, 21, 16, 18, 95],[47, 26, 71, 38, 69, 12],[67, 99, 35, 94, 3, 11],[22, 33, 73, 64, 41, 11], [53, 68, 47, 44, 62, 57], [37, 59, 23, 41, 29, 78], [16, 35, 90, 42, 88, 6], [40, 42, 64, 48, 46, 5], [90, 29, 70, 50, 6, 1], [93, 48, 29, 23, 84, 54], [56, 40, 66, 76, 31, 8]], 2, 1)
result = e.query(index, [5,5,5], 5, 1)
```

# Datasets
A little bit of information about the datasets that have been used for testing.
| Dataset                                                           | Dimensions | Train size | Test size | Neighbors | Distance  |                                                                  
| ----------------------------------------------------------------- | ---------: | ---------: | --------: | --------: | --------- | 
| random-xs-20-euclidean											|        20  |     9000   |    1000   |       10  | Euclidean |
| random-xs-20-angular                       			    		|        20  |     9000   |    1000   |       10  | Angular   |
| random-s-100-euclidean                      			    		|        100 |     9000   |    1000   |       10  | Euclidean |
| [MNIST](http://yann.lecun.com/exdb/mnist/)                        |        784 |     60,000 |    10,000 |       100 | Euclidean |
| [Fashion-MNIST](https://github.com/zalandoresearch/fashion-mnist) |        784 |     60,000 |    10,000 |       100 | Euclidean |
| [SIFT](https://corpus-texmex.irisa.fr/)                           |        128 |  1,000,000 |    10,000 |       100 | Euclidean |
| [GloVe](http://nlp.stanford.edu/projects/glove/)                  |         25 |  1,183,514 |    10,000 |       100 | Angular   |
