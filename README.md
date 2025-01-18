# Jolt-Godot

In this example I create the modlue [jolt_physics](https://github.com/hugarty/Jolt-Godot/tree/jolt/godot-4.3-stable/modules/jolt_physics) inside godot and the SCsub don't have the defines.


**You need to create the libpath folder and put the STATIC LIB there.**

I create a simple Static Library changing the [CMakeLists.txt](https://github.com/hugarty/Jolt-Godot/blob/jolt/JoltPhysicsHelloWorld-main/Build/CMakeLists.txt#L192).

```
./godot-4.3-stable/modules/jolt_physics
 | libpath/
 |   ` libJoltStatic.a
 | src/
 |   ` Jolt/
 |   ` Source/
 |      ` libraryJoltHelloWorld.h
 |      ` libraryJoltHelloWorld.cpp
 | config.py
 | register_types.cpp
 | register_types.h
 | SCsub
 | godotJolt.cpp
 | godotJolt.h
```
