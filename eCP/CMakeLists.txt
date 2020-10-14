cmake_minimum_required(VERSION 3.18)

project(
    ECP
    VERSION 1.0
    DESCRIPTION "eCP algorithm C++ implementation"
    LANGUAGES CXX)

 # Must be in main file
enable_testing()

# The compiled library code, executable code, external libs and tests
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(extern)
add_subdirectory(tests)