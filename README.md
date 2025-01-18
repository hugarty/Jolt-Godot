# Jolt-Godot

I just followed this [tutorial](https://docs.godotengine.org/en/stable/contributing/development/core_and_modules/binding_to_external_libraries.html), but for a simple lib Summator instead of TTS.

It compiles well and the godotExampleProject folder has a sample project that can run and execute Summator.

Simple view of the module inside godot:

```
./godot-4.3-stable/modules/summator
 | libpath/
 |   ` libSummator.a
 | src/
 |   ` include/
 |   |  ` Summator.h
 |   ` Summator.cpp
 | config.py
 | register_types.cpp
 | register_types.h
 | SCsub
 | godot_summator.cpp
 | godot_summator.h
```

Simple step-by-step to compile godot and bind the STATIC lib:
1. Compile Summator with cmake
```
$ cmake -B [YOUR PATH TO THE PROJECT]/Summator/build -S [YOUR PATH TO THE PROJECT]/Summator/
$ make all -C  [YOUR PATH TO THE PROJECT]/Summator/build
```
2. copy ``[PROJECTROOT]/Summator/build/src/libSummator.a`` to ``[PROJECTROOT]/godot-4.3-stable/modules/summator/libpath/`` 
3. copy the .cpp and .h from ``[PROJECTROOT]/Summator/build/src/libSummator.a`` to ``[PROJECTROOT]/godot-4.3-stable/modules/summator/src/``
4. create the files needed by godot: *config.py, SCsub, godot_summator.cpp, godot_summator.h, register_types.cpp* and *register_types.h*
5. If you are using linux run ``scons platfor=linuxbsd`` to compile godot and bind the library.
