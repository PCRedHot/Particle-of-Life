#! /bin/sh

# cd external/glew/build ; cmake ./cmake ; make -j4
# cd ../../..

cmake -S . -B out/build
cd out/build ; make