#!/bin/bash
cd $( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

LD_LIBRARY_PATH=/usr/local/lib
export LD_LIBRARY_PATH
./server.run
