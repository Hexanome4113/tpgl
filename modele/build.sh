#!/bin/bash

mkdir build
cd build
cmake ..
make
echo "executable généré: ./build/gl"
