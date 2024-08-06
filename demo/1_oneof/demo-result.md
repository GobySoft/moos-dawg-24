# Proto definition

```
Please note that for Google Protobuf versions < 2.5.0, the dccl extensions will not be show below, so you'll need to refer to the original .proto file.
message Command {
  option (.dccl.msg) = {
    id: 124
    max_bytes: 32
    codec_version: 4
    unit_system: "si"
  };
  message ThermoclineParams {
    required int32 max_search_depth = 1 [(.dccl.field) = {
      min: 10
      max: 1000
      units {
        derived_dimensions: "length"
      }
    }];
  }
  message FrontParams {
    required double temperature_threshold = 1 [(.dccl.field) = {
      min: 0.1
      max: 2
      resolution: 0.1
      units {
        derived_dimensions: "temperature"
        system: "celsius"
        relative_temperature: true
      }
    }];
  }
  message PlaneParams {
    required int32 center_freq = 1 [(.dccl.field) = {
      min: 30000
      max: 40000
      resolution: 100
      units {
        derived_dimensions: "frequency"
      }
    }];
    required int32 bandwidth = 2 [(.dccl.field) = {
      min: 100
      max: 10000
      resolution: 100
      units {
        derived_dimensions: "frequency"
      }
    }];
  }
  enum Action {
    MEASURE_THERMOCLINE = 1;
    SEARCH_FOR_OCEAN_FRONT = 2;
    SEARCH_FOR_MISSING_AIRPLANE = 3;
  }
  required .moos.dawg.Command.Action action = 1;
  oneof parameters {
    .moos.dawg.Command.ThermoclineParams thermocline = 2;
    .moos.dawg.Command.FrontParams front = 3;
    .moos.dawg.Command.PlaneParams airplane = 4;
  }
}
message CommandWithoutOneOf {
  option (.dccl.msg) = {
    id: 125
    max_bytes: 32
    codec_version: 3
    unit_system: "si"
  };
  required .moos.dawg.Command.Action action = 1;
  optional .moos.dawg.Command.ThermoclineParams thermocline = 2;
  optional .moos.dawg.Command.FrontParams front = 3;
  optional .moos.dawg.Command.PlaneParams airplane = 4;
}
```


# Analyze (DCCL3: without oneof)

```
== 125: moos.dawg.CommandWithoutOneOf {0x02c62506a7b294a2} ==
Actual maximum size of message: 6 bytes / 48 bits
        dccl.id head...........................8
        user head..............................0
        body..................................34
        padding to full byte...................6
Allowed maximum size of message: 32 bytes / 256 bits
--------------------------- Header ---------------------------
dccl.id head...................................8 {dccl.default.id}
---------------------------- Body ----------------------------
moos.dawg.CommandWithoutOneOf...............5-34 {dccl.default3}
        1. action..............................2 {dccl.default3}
        2. thermocline......................1-11 {dccl.default3}
                1. max_search_depth...................10 {dccl.default3}
        3. front.............................1-6 {dccl.default3}
                1. temperature_threshold...............5 {dccl.default3}
        4. airplane.........................1-15 {dccl.default3}
                1. center_freq.........................7 {dccl.default3}
                2. bandwidth...........................7 {dccl.default3}
```


# Analyze (DCCL4: oneof)

```
======== 124: moos.dawg.Command {0x3dabf069f95d1b7b} ========
Actual maximum size of message: 4 bytes / 32 bits
        dccl.id head...........................8
        user head..............................0
        body..................................18
        padding to full byte...................6
Allowed maximum size of message: 32 bytes / 256 bits
--------------------------- Header ---------------------------
dccl.id head...................................8 {dccl.default.id}
---------------------------- Body ----------------------------
moos.dawg.Command...........................4-18 {dccl.default4}
        0. parameters [oneof]...............2-16 {
            2. thermocline........................10 {dccl.default4}
                1. max_search_depth...................10 {dccl.default4}
            3. front...............................5 {dccl.default4}
                1. temperature_threshold...............5 {dccl.default4}
            4. airplane...........................14 {dccl.default4}
                1. center_freq.........................7 {dccl.default4}
                2. bandwidth...........................7 {dccl.default4}
        }
        1. action..............................2 {dccl.default4}
```


# Example 1 (MEASURE_THERMOCLINE)
- Original: **action: MEASURE_THERMOCLINE thermocline { max_search_depth: 100 }**
- Encoded (hex)
  - without oneof: fad402 (**3 bytes**)
  - oneof: f8a105 (**3 bytes**)
- Decoded:
  - without oneof: |moos.dawg.CommandWithoutOneOf| action: MEASURE_THERMOCLINE thermocline { max_search_depth: 100 }
  - oneof: |moos.dawg.Command| action: MEASURE_THERMOCLINE thermocline { max_search_depth: 100 }


# Example 2 (SEARCH_FOR_OCEAN_FRONT)
- Original: **action: SEARCH_FOR_OCEAN_FRONT front { temperature_threshold: 0.9 }**
- Encoded (hex)
  - without oneof: fa8900 (**3 bytes**)
  - oneof: f88600 (**3 bytes**)
- Decoded:
  - without oneof: |moos.dawg.CommandWithoutOneOf| action: SEARCH_FOR_OCEAN_FRONT front { temperature_threshold: 0.9 }
  - oneof: |moos.dawg.Command| action: SEARCH_FOR_OCEAN_FRONT front { temperature_threshold: 0.9 }


# Example 3 (SEARCH_FOR_MISSING_AIRPLANE)
- Original: **action: SEARCH_FOR_MISSING_AIRPLANE airplane { center_freq: 37500 bandwidth: 1000 }**
- Encoded (hex)
  - without oneof: fa729900 (**4 bytes**)
  - oneof: f8bb4c00 (**4 bytes**)
- Decoded:
  - without oneof: |moos.dawg.CommandWithoutOneOf| action: SEARCH_FOR_MISSING_AIRPLANE airplane { center_freq: 37500 bandwidth: 1000 }
  - oneof: |moos.dawg.Command| action: SEARCH_FOR_MISSING_AIRPLANE airplane { center_freq: 37500 bandwidth: 1000 }

