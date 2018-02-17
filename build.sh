#/bin/bash

BUILD_DIR="build/"

echo ">> Cleaning old build (if any)"
rm -rf $BUILD_DIR

echo ">> Creating build directory: $PWD/$BUILD_DIR"
mkdir -p $BUILD_DIR

echo ">> Entering build directory: $PWD/$BUILD_DIR"
cd $BUILD_DIR

echo ">> Running cmake ..."
cmake ..

echo ">> Running make ..."
make

echo ">> DONE"
