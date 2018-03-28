#/bin/bash

BUILD_DIR="$PWD/build/"

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

echo ">> Installing TypeScript compiler: $PWD/$BUILD_DIR"
npm install typescript@2.8.2 --prefix="$BUILD_DIR" > /dev/null 2>&1

if [[ $? -ne 0 ]]; then
    echo 
    echo "#######################################################"
    echo "# Failed to install typescript                        #"
    echo "# You will not be able to execute the generated code  #."
    echo "#######################################################"
    echo
fi

echo ">> DONE"
