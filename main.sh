#!/bin/bash

AOC_IMAGE="aoc"

docker build -t $AOC_IMAGE .

sudo modprobe msr

docker run --rm \
           --privileged \
           -v $(pwd):/usr/src/aoc_raw \
           $AOC_IMAGE \
           bash -c " git clone https://github.com/ma87/KulKod /usr/src/KulKod ;
               cd /usr/src/KulKod ;
               mkdir build ;
               cd build ;
               cmake -DCMAKE_INSTALL_PREFIX=/usr .. ;
               make energy_measurement ;
               make install ;
               cd /usr/src/aoc_raw ;
               ./run_measures.sh
           "
