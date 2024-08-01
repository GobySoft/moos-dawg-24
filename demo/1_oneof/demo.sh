#!/bin/bash

function user_wait()
{
    read -p "Press any key to continue..." -n1 -s
    echo
}

function encode_decode_demo()
{
    original="$1"
    echo "- Original: **${original}**"
    encoded=$(echo "$original" | dccl -f command.proto --message moos.dawg.Command --encode --format hex)
    encodedv3=$(echo "$original" | dccl -f command.proto --message moos.dawg.CommandWithoutOneOf --encode --format hex)
    echo "- Encoded (hex)"
    echo "  - without oneof: $encodedv3 (**$((${#encodedv3}/2)) bytes**)"
    echo "  - oneof: $encoded (**$((${#encoded}/2)) bytes**)"
    decoded=$(echo -n "$encoded"  | dccl -f command.proto --decode --format hex)
    decodedv3=$(echo -n "$encodedv3"  | dccl -f command.proto --decode --format hex)
    echo "- Decoded:"    
    echo "  - without oneof: ${decodedv3}"
    echo "  - oneof: ${decoded}"
}


(echo "# Proto definition"
echo ''
echo '```'
dccl --display_proto --proto_file command.proto
echo '```') | md.py

user_wait

(echo "# Analyze (DCCL3: without oneof)"
echo ''
echo '```'
dccl --analyze --proto_file command.proto -m moos.dawg.CommandWithoutOneOf
echo '```') | md.py

user_wait

(echo "# Analyze (DCCL4: oneof)"
echo ''
echo '```'
dccl --analyze --proto_file command.proto -m moos.dawg.Command
echo '```') | md.py

user_wait


(echo "# Example 1 (MEASURE_THERMOCLINE)"
original1="action: MEASURE_THERMOCLINE thermocline { max_search_depth: 100 }"
encode_decode_demo "$original1") | md.py

user_wait

(echo "# Example 2 (SEARCH_FOR_OCEAN_FRONT)"
original2="action: SEARCH_FOR_OCEAN_FRONT front { temperature_threshold: 0.9 }"
encode_decode_demo "$original2") | md.py

user_wait

(echo "# Example 3 (SEARCH_FOR_MISSING_AIRPLANE)"
original3="action: SEARCH_FOR_MISSING_AIRPLANE airplane { center_freq: 37500 bandwidth: 1000 }"
encode_decode_demo "$original3") | md.py

