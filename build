#!/bin/bash

# output directory

target="Build/$1"

# generate cmake build files

cmake -S . -B $target -DCMAKE_BUILD_TYPE=$1 -DNO_OS:BOOL=ON

# compile cmake build files

cmake --build $target --config $1
