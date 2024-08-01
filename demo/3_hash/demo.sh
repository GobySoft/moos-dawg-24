#!/bin/bash

function user_wait()
{
    read -p "Press any key to continue..." -n1 -s
    echo
}

protoc --python_out=. original_command_with_hash.proto
protoc --python_out=. updated_command_with_hash.proto


(echo "# Updated command (diff)"
echo ''
echo '```'
diff -u command.proto updated_command.proto
echo '```') | md.py

user_wait

(echo "# Updated command with hash (diff)"
echo ''
echo '```'
diff -u updated_command.proto updated_command_with_hash.proto
echo '```') | md.py

user_wait


(echo "# Hash via CLI (Static analysis)"
 echo ''
 echo "- Original Hash: "
 dccl --analyze --proto_file command.proto -m moos.dawg.Command -H
 echo "- Updated Hash: "
 dccl --analyze --proto_file updated_command.proto -m moos.dawg.Command -H
 echo ""
 echo "When possible you can compare these at compile time to detect unexpected backwards compatibility problems"
) | md.py

user_wait

./demo.py |& ./md.py



