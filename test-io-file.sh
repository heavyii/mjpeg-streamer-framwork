#!/bin/sh
export LD_LIBRARY_PATH=`pwd`
./mjpg_streamer -i "input_file.so -f INSTALL" -o "output_file.so  -f `pwd`"

