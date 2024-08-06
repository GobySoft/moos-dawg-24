# Proto definition 
```
message Status {
  option (.dccl.msg) = {
    id: 126
    max_bytes: 32
    codec_version: 4
    unit_system: "si"
  };
  message Location {
    required int32 x = 1 [(.dccl.field) = {
      min: -10000
      max: 10000
      resolution: 1
      units {
        derived_dimensions: "length"
      }
    }];
    required int32 y = 2 [(.dccl.field) = {
      min: -10000
      max: 10000
      resolution: 1
      units {
        derived_dimensions: "length"
      }
    }];
    optional int32 depth = 3 [(.dccl.field) = {
      min: 0
      max: 5000
      resolution: 0.1
      units {
        derived_dimensions: "length"
      }
      dynamic_conditions {
        omit_if: "root.type == \'USV\'"
        max: "if root.type == \'DEEP_AUV\' then return 5000 else return 100 end"
      }
    }];
  }
  message AirplaneDetection {
    required int32 detected_depth = 1 [(.dccl.field) = {
      min: 0
      max: 5000
      resolution: 0.1
      units {
        derived_dimensions: "length"
      }
    }];
    required int32 detected_freq = 2 [(.dccl.field) = {
      min: 30000
      max: 40000
      resolution: 100
      units {
        derived_dimensions: "frequency"
      }
    }];
  }
  enum VehicleType {
    USV = 1;
    AUV_WITH_CTD = 2;
    AUV_WITH_SONAR = 3;
    DEEP_AUV = 4;
  }
  required .moos.dawg.Status.VehicleType type = 1;
  required .moos.dawg.Status.Location location = 2;
  optional double temperature = 3 [(.dccl.field) = {
    min: 0
    max: 40
    resolution: 0.01
    units {
      derived_dimensions: "temperature"
      system: "celsius"
      relative_temperature: false
    }
    dynamic_conditions {
      only_if: "this.type == \'AUV_WITH_CTD\' or this.type == \'DEEP_AUV\'"
    }
  }];
  optional .moos.dawg.Status.AirplaneDetection airplane_detection = 4 [(.dccl.field) = {
    dynamic_conditions {
      only_if: "this.type == \'AUV_WITH_SONAR\'"
    }
  }];
}

message StatusWithoutDynamicConditions {
  option (.dccl.msg) = {
    id: 127
    max_bytes: 32
    codec_version: 3
    unit_system: "si"
  };
  message Location {
    required int32 x = 1 [(.dccl.field) = {
      min: -10000
      max: 10000
      resolution: 1
      units {
        derived_dimensions: "length"
      }
    }];
    required int32 y = 2 [(.dccl.field) = {
      min: -10000
      max: 10000
      resolution: 1
      units {
        derived_dimensions: "length"
      }
    }];
    optional int32 depth = 3 [(.dccl.field) = {
      min: 0
      max: 5000
    }];
  }
  required .moos.dawg.Status.VehicleType type = 1;
  required .moos.dawg.StatusWithoutDynamicConditions.Location location = 2;
  optional double temperature = 3 [(.dccl.field) = {
    min: 0
    max: 40
    resolution: 0.01
    units {
      derived_dimensions: "temperature"
      system: "celsius"
      relative_temperature: false
    }
  }];
  optional .moos.dawg.Status.AirplaneDetection airplane_detection = 4;
}

```
# Analyze (DCCL3: No dynamic conditions) 
```
 127: moos.dawg.StatusWithoutDynamicConditions {0xbbe61b9a166dd7f5} 
Actual maximum size of message: 12 bytes / 96 bits
        dccl.id head...........................8
        user head..............................0
        body..................................81
        padding to full byte...................7
Allowed maximum size of message: 32 bytes / 256 bits
--------------------------- Header ---------------------------
dccl.id head...................................8 {dccl.default.id}
---------------------------- Body ----------------------------
moos.dawg.StatusWithoutDynamicConditions...58-81 {dccl.default3}
        1. type................................2 {dccl.default3}
        2. location...........................43 {dccl.default3}
                1. x..................................15 {dccl.default3}
                2. y..................................15 {dccl.default3}
                3. depth..............................13 {dccl.default3}
        3. temperature........................12 {dccl.default3}
        4. airplane_detection...............1-24 {dccl.default3}
                1. detected_depth.....................16 {dccl.default3}
                2. detected_freq.......................7 {dccl.default3}
```
# Analyze (DCCL4: Dynamic conditions) 
```
========= 126: moos.dawg.Status {0x5eca4a25746d2288} =========
Actual maximum size of message: 12 bytes / 96 bits
        dccl.id head...........................8
        user head..............................0
        body..................................84
        padding to full byte...................4
Allowed maximum size of message: 32 bytes / 256 bits
--------------------------- Header ---------------------------
dccl.id head...................................8 {dccl.default.id}
---------------------------- Body ----------------------------
moos.dawg.Status............................0-84 {dccl.default4}
        1. type................................2 {dccl.default4}
        2. location.........................0-46 {dccl.default4}
                1. x..................................15 {dccl.default4}
                2. y..................................15 {dccl.default4}
                3. depth..............................16 {dccl.default4}
        3. temperature........................12 {dccl.default4}
        4. airplane_detection...............1-24 {dccl.default4}
                1. detected_depth.....................16 {dccl.default4}
                2. detected_freq.......................7 {dccl.default4}
```
# Example 1 

- Original: **type: USV location { x: 500 y: 700 }**
- Encoded (hex)
  - without dynamic conditions: fe10a4985300000000 (9 bytes)
  - dynamic conditions: fc10a49853 (5 bytes)
- Decoded:
  - without dynamic conditions: type: USV location { x: 500 y: 700 }
  - dynamic conditions: type: USV location { x: 500 y: 700 }
# Example 2 

## Example 2a  

- Original: **type: AUV_WITH_CTD location { x: 500 y: 700 depth: 50 } temperature: 12.3**
- Encoded (hex)
  - without dynamic conditions: fe11a4985333e09900 (9 bytes)
  - dynamic conditions: fc11a49853f53913 (8 bytes)
- Decoded:
  - without dynamic conditions: type: AUV_WITH_CTD location { x: 500 y: 700 depth: 50 } temperature: 12.3
  - dynamic conditions: type: AUV_WITH_CTD location { x: 500 y: 700 depth: 50 } temperature: 12.3
## Example 2b  

- Original: **type: AUV_WITH_CTD location { x: 500 y: 700 depth: 2100 } temperature: 12.3**
- Exception (expected) as we exceeded dynamic max on depth field: 
```
Message: moos.dawg.Status.Location: Field: moos.dawg.Status.Location.depth: Value exceeds min/max bounds for field: optional int32 depth = 3 [(.dccl.field) = {
  min: 0
  max: 5000
  resolution: 0.1
  units {
    derived_dimensions: "length"
  }
  dynamic_conditions {
    omit_if: "root.type == \'USV\'"
    max: "if root.type == \'DEEP_AUV\' then return 5000 else return 100 end"
  }
}];

```
## Example 2c  

- Original: **type: DEEP_AUV location { x: 500 y: 700 depth: 2100 } temperature: 12.3**
- Encoded (hex)
  - without dynamic conditions: fe13a4985335e89900 (9 bytes)
  - dynamic conditions: fc13a498530952ce04 (9 bytes)
- Decoded:
  - without dynamic conditions: type: DEEP_AUV location { x: 500 y: 700 depth: 2100 } temperature: 12.3
  - dynamic conditions: type: DEEP_AUV location { x: 500 y: 700 depth: 2100 } temperature: 12.3
# Example 3 

- Original: **type: AUV_WITH_SONAR location { x: 500 y: 700 depth: 10 } airplane_detection { detected_depth: 4100 detected_freq: 38000 }**
- Encoded (hex)
  - without dynamic conditions: fe12a498530b0000a2804201 (12 bytes)
  - dynamic conditions: fc12a498536544018502 (10 bytes)
- Decoded:
  - without dynamic conditions: type: AUV_WITH_SONAR location { x: 500 y: 700 depth: 10 } airplane_detection { detected_depth: 4100 detected_freq: 38000 }
  - dynamic conditions: type: AUV_WITH_SONAR location { x: 500 y: 700 depth: 10 } airplane_detection { detected_depth: 4100 detected_freq: 38000 }

