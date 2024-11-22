#/bin/bash

cd "$(dirname "$0")"


cd ..

if [ -d "build/" ]
then
	echo "Running..."
	./build/ldp-intermedio
else
	echo "Directory build does not exist!"
fi

