
#ifndef MMO_FILHO_H
#define MMO_FILHO_H

#include "core/object/ref_counted.h"

#include "libraryJoltHelloWorld.h"


class MMOFilho : public RefCounted {
	GDCLASS(MMOFilho, RefCounted);

    FirstPhysicsManager* firstPhysicsManager;

protected:
	static void _bind_methods();

public:
	MMOFilho();

    void addCharacter();

    // void getCharacterPosition();

    void update();
};

#endif // MMO_FILHO_H