#!/bin/bash

cd "$(dirname "$0")"

cd ..;

if [ -d "build/" ]
then
	cd build/
	./ldp-intermedio
else
    echo "Error: Directory build does not exist."
fi
