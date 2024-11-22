#/bin/bash

cd "$(dirname "$0")"

cd ..

if [ -d "build/" ]; then
  echo "Building..."
else
  echo "Directory build does not exist, creating it..."
  mkdir build
fi

g++ src/main.cpp src/LidarDriver.cpp -o build/ldp-intermedio
