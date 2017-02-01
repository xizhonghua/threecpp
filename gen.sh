#!/bin/bash
echo generating...

SRC_DIR="../../src"

mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug $SRC_DIR
cd -

mkdir -p build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release $SRC_DIR
cd -

if [[ "$OSTYPE" == "darwin"* ]]; then
  mkdir -p build/xcode
  cd build/xcode
  cmake -G Xcode $SRC_DIR
fi

echo "done..."