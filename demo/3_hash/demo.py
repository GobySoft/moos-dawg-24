#!/usr/bin/env python3
import os, dccl
import original_command_with_hash_pb2
import updated_command_with_hash_pb2

def encode_decode_demo(codec, codec_updated, command):
    
    updated = updated_command_with_hash_pb2.UpdatedCommandWithHash()

    print(f"- Original: **{str(command)[:-1]}**")
    encoded = codec.encode(command)
    
    print("- Encoded (hex)")
    print(f"  - {encoded.hex()} ({len(encoded)} bytes)")

    decoded = codec.decode(encoded)

    print("- Decoded:")
    print(f"  - Using original message: {decoded}")

    try:
        decoded_updated = codec_updated.decode(encoded)
    except dccl.DcclException as e:
        print (f"  - Using updated message: Exception: {e}")



dccl.loadProtoFile(os.path.abspath("./original_command_with_hash.proto"))
dccl.loadProtoFile(os.path.abspath("./updated_command_with_hash.proto"))

codec = dccl.Codec()
codec.load("moos.dawg.OriginalCommandWithHash")
codec.set_strict(True)

# Receiver with updated message
codec_updated = dccl.Codec()
codec_updated.load("moos.dawg.UpdatedCommandWithHash")
codec_updated.set_strict(True)

command = original_command_with_hash_pb2.OriginalCommandWithHash(action=original_command_with_hash_pb2.OriginalCommandWithHash.MEASURE_THERMOCLINE, thermocline = {"max_search_depth": 100}, hash=0)

print("# Hash via Message field (Runtime check)")
encode_decode_demo(codec, codec_updated, command)
