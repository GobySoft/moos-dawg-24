# moos-dawg-24
Demonstrations for MOOS-DAWG 2024 talk ([DCCL4 in MOOS](presentation/schneider-moos-dawg-2024-dccl4.pdf)).

Requires MOOS, Goby, DCCL, Python to run all the examples.

The demo intentionally use a mix of shell scripts, C++, and Python to show the various ways you can interact with DCCL. 

## Run in docker

The easiest way to start playing with these examples is to run them in docker. To do so, install docker and run

```
docker run -it gobysoft/moos-dawg-2024
```

If you want to install the dependencies to run on your Ubuntu machine, take a look at the `docker/Dockerfile`.

## Demo 1 (oneof)

This example demonstrates the use of `oneof` in DCCL using the `dccl` command line tool.

To run:
```
cd /opt/moos-dawg-24/demo/1_oneof
./demo.sh
```

or you can look at the [command.proto](demo/1_oneof/command.proto) DCCL message used by the [demo.sh](demo/1_oneof/demo.sh) shell script to produce the [generated output](demo/1_oneof/demo-result.md). 

## Demo 2 (dynamic conditions)

This example demonstrates the use of Dynamic Conditions using C++.

To run:
```
cd /opt/moos-dawg-24/demo/2_dynamic_conditions
./demo.sh
```

or you can look at the [status.proto](demo/2_dynamic_conditions/status.proto) DCCL message used by [demo.cpp](demo/2_dynamic_conditions/demo.cpp) C++ code as called by the [demo.sh](demo/2_dynamic_conditions/demo.sh) shell script to produce the [generated output](demo/2_dynamic_conditions/demo-result.md). 

## Demo 3 (message hash)

This example demonstrates the use of message hashing using the `dccl` command line tool (for static hash comparison) and Python (for messages based hash comparison).

```
cd /opt/moos-dawg-24/demo/3_hash
./demo.sh
```


or you can look at the [original_command_with_hash.proto](demo/3_hash/original_command_with_hash.proto) and [updated_command_with_hash.proto](demo/3_hash/updated_command_with_hash.proto) DCCL messages used by the [demo.py](demo/3_hash/demo.py) Python code as called by the [demo.sh](demo/3_hash/demo.sh) shell script to produce the [generated output](demo/3_hash/demo-result.md). 

## Demo 4 (MOOS example)

This example uses two C++ MOOS apps (pCommand and pSender) to demonstrate using the Goby3 pAcommsHandler to send messages between two communities (using UDP in this example, but this could be swapped for any Goby modem driver for acoustics, satcomms, etc.).

```
cd /opt/moos-dawg-24/demo/4_moos
./demo.sh
```

Then you can look at the output of uXMS, etc. one at a time using

```
screen -r mm1.uXMS
CTRL-A D
screen -r mm2.uXMS
CTRL-A D
// etc.
```