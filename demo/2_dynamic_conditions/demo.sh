#!/bin/bash

set -u -e

protoc --cpp_out=. status.proto --dccl_out=.
c++ demo.cpp status.pb.cc -o demo -ldccl -lprotobuf
./demo |& ./md.py
