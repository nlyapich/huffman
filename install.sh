#!/bin/bash

sudo apt-get update

sudo apt-get -y install libboost-all-dev

sudo apt-get -y install cmake

sudo apt-get -y install qt5-default

if ! [ -d ./build]; then
  rm -R ./build
fi

mkdir ./build && cd ./build

testing_status=false
while [ -n "$1" ]
do
case "$1" in
  -t)
    cmake .. -DBUILD_TESTING=ON
    testing_status=true
  ;;
  *)
    echo "$1 is not an option"
  ;;
esac
shift
done

if [ "$testing_status" ]; then
  cmake ..
fi

cmake --build .
