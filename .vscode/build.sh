#!/bin/bash
cd ../
mkdir build
cd ./build
export PATH="/usr/lib/ccache/:$PATH"
cmake ..
make
