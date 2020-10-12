cmake_minimum_required(VERSION 3.18)

project(
    ECP
    VERSION 1.0
    DESCRIPTION "eCP algorithm C++ implementation"
    LANGUAGES CXX)

# The compiled library code and the executable code
add_subdirectory(src)
add_subdirectory(app)

