# Extended Cluster-Pruning
The extended cluster-pruning algorithm is implemented in C++ and provides a python wrapper for usage within the [ANN-benchmarking tool](https://github.com/erikbern/ann-benchmarks/) to compare with other state of the art ANN algorithms. 

Initially proposed as a bachelors project at the IT-University of Copenhagen in spring 2020. This repository continues the work by building a dynamic extension of the algorithm ontop of the original implementation.

This project is currently a work in progress. See [CONTRIBUTING.md](CONTRIBUTING.md) on how to contribute.

## Project dependencies
```
gcc, c++, cmake, python3.6, swig, docker
```

# How-to's
## How to compile eCP
- If you have CMake installed it should not be problematic using your favorite IDE. Load the `CMakeLists.txt` file in the root dir and CMake will take care of the rest.
Currently only GNU/GCC is known to be supported.

- In case you are interested in manually running commands visit `./eCP/scripts/` where there are examples of different basic interactions with CMake from the command line.

## How to run eCP in ANN-Benchmarks
The following descriptions assumes some sort of Linux distribution even if the eCP source code will compile on e.g. Windows.
It is also assumed that `./` is the root of this repository.

1. To build the Python based wrapper around the C++ eCP implementation:
    - Install Swig e.g. on Debian based distros: ```sudo apt-get install -y swig```.
    - Goto `./scripts/`
    - Run `./generate_wrapper.sh`.
2. Go to `./ann_benchmarks/install/Dockerfile.ecp` and change what repository is cloned. Make it point to the current working branch or whichever branch you are working on. The reason is that ANN-Benchmarks will pull in and build the given repository before running tests on it.

3. Now it is possible to install eCP into ANN-Benchmarks by executing the script `./scipts/ecp_install.sh`, which will pull down ANN-Benchmarks repository and copy the eCP integration into the newly cloned repository. Here the Python requirements will be installed and finally the ANN-Benchmarks install script will be called to setup only the eCP algorithm, i.e. build a Docker image containing a compiled executable of the code from the designated branch from earlier.


# Documentation
## Wrapper interface
SWIG is used to construct the Python-based wrapper around the C++ code. SWIG is
handled by Cmake which will recompile the wrapper every time the code base is
recompiled. This will also happen inside the docker container, when the code is
sent to the Ann-Benchmarks framework for testing.

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
