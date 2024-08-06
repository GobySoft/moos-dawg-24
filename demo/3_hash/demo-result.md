# Updated command (diff)

```
--- command.proto	2024-08-01 16:58:45.071139498 -0400
+++ updated_command.proto	2024-08-01 16:58:49.106890224 -0400
@@ -18,6 +18,7 @@
         MEASURE_THERMOCLINE = 1;
         SEARCH_FOR_OCEAN_FRONT = 2;
         SEARCH_FOR_MISSING_AIRPLANE = 3;
+        FIND_LIFE_ON_MARS = 4;
     }
 
     message ThermoclineParams
```


# Updated command with hash (diff)

```
--- updated_command.proto	2024-08-01 16:58:49.106890224 -0400
+++ updated_command_with_hash.proto	2024-08-01 16:57:54.902237354 -0400
@@ -4,7 +4,7 @@
 
 package moos.dawg;
 
-message Command
+message UpdatedCommandWithHash
 {
     option (dccl.msg) = {
         id: 124
@@ -68,4 +68,7 @@
         FrontParams front = 3;     // for action == SEARCH_FOR_OCEAN_FRONT
         PlaneParams airplane = 4;  // for action == SEARCH_FOR_MISSING_AIRPLANE
     }
+
+    required uint32 hash = 5
+        [(dccl.field).codec = "dccl.hash", (dccl.field).max = 0xFFFF];
 }
```


# Hash via CLI (Static analysis)

- Original Hash: 
0x3dabf069f95d1b7b
- Updated Hash: 
0xa4cb90cf16c8027e

When possible you can compare these at compile time to detect unexpected backwards compatibility problems


# Hash via Message field (Runtime check)
- Original: **action: MEASURE_THERMOCLINE
thermocline {
  max_search_depth: 100
}
hash: 0**
- Encoded (hex)
  - f8a1057613 (5 bytes)
- Decoded:
  - Using original message: action: MEASURE_THERMOCLINE
thermocline {
  max_search_depth: 100
}
hash: 19928

  - Using updated message: Exception: Message f8a1057613 failed to decode. Reason: Message: moos.dawg.UpdatedCommandWithHash: Hash value mismatch. Expected: 21567, received: 19928. Ensure both sender and receiver are using identical DCCL definitions


