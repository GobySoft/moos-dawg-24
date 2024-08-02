#!/bin/bash

(mkdir -p apps/build
cd apps/build
cmake ..
make)

export PATH=./apps/build:$PATH

which pCommand pStatus

pAntler mm1.moos &
pAntler mm2.moos &


trap "trap - SIGTERM && kill -- -$$" SIGINT SIGTERM EXIT

while [ 1 ]; do sleep 1; done

