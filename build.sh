#! /bin/sh

# cd external/glew/build ; cmake ./cmake ; make -j4
# cd ../../..

cmake -S . -B out/build -DCMAKE_BUILD_TYPE=Debug
cd out/build ; make