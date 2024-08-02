#!/bin/bash

./stop_moos.sh

(mkdir -p apps/build
cd apps/build
cmake ..
make)

export PATH=./apps/build:$PATH

which pCommand pStatus

pAntler mm1.moos >& /dev/null &
pAntler mm2.moos >& /dev/null &

sleep 1

screen -ls
