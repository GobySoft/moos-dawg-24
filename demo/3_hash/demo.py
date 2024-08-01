import os, dccl, command_pb2

dccl.loadProtoFile(os.path.abspath("./command.proto"))

codec = dccl.Codec()
codec.load("moos.dawg.OriginalCommandWithHash")

r_out = command_pb2.OriginalCommandWithHash(action=command_pb2.OriginalCommandWithHash.MEASURE_THERMOCLINE, thermocline = {temperature_threshold: 1.2})

print(r_out)
