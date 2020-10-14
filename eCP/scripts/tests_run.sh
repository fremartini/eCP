#! /usr/bin/env bash

# This script will run the eCP test suite

cd ../build/tests/
exec ctest -C Debug -V
