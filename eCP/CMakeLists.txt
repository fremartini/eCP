cmake_minimum_required(VERSION 3.18)

project(
    ECP
    VERSION 1.0
    DESCRIPTION "eCP algorithm C++ implementation"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE on)

# Must be in main file
enable_testing()

# External dependencies not resolved by CMake
find_package(SWIG COMPONENTS python)
find_package(HDF5 REQUIRED COMPONENTS CXX)

# - The compiled library code, executable code, external libs, swig config and tests -
add_subdirectory(src)
add_subdirectory(main)
add_subdirectory(extern)
add_subdirectory(tests)
add_subdirectory(swig)

message("Input C++ compiler flags: ${CMAKE_CXX_FLAGS}")
