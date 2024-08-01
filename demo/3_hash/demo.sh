#!/bin/bash

function user_wait()
{
    read -p "Press any key to continue..." -n1 -s
    echo
}

protoc --python_out=. command.proto 

(echo "# Hash via CLI"
echo ''
echo "- Original Hash: "
dccl --analyze --proto_file ../1_oneof/command.proto -m moos.dawg.Command -H
echo "- Updated Hash: "
dccl --analyze --proto_file command.proto -m moos.dawg.Command -H

) | md.py

#user_wait


