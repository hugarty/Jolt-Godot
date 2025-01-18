# Jolt-Godot

This example is almost the same of the branch [jolt](https://github.com/hugarty/Jolt-Godot/tree/jolt).


The difference is that I remove all ``target_compile_definitions`` from ``Jolt.cmake`` except ``JPH_CROSS_PLATFORM_DETERMINISTIC``. I also added to [SCsub](https://github.com/hugarty/Jolt-Godot/blob/jolt-cross-platform-deterministic/godot-4.3-stable/modules/jolt_physics/SCsub#L170) ``env.Append(CPPDEFINES=["JPH_CROSS_PLATFORM_DETERMINISTIC"])``.


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
