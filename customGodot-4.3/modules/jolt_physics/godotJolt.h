
#ifndef GODOT_JOLT_H
#define GODOT_JOLT_H

#include "core/object/ref_counted.h"

#include <libraryJoltHelloWorld.h>


class GodotJolt : public RefCounted {
	GDCLASS(GodotJolt, RefCounted);

    FirstPhysicsManager* firstPhysicsManager;

protected:
	static void _bind_methods();

public:
	GodotJolt();

    void addCharacter();
    void update();
};

#endif 