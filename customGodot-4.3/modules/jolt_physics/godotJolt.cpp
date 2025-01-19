
#include "core/object/ref_counted.h"
#include "godotJolt.h"


void GodotJolt::_bind_methods() {
    ClassDB::bind_method(D_METHOD("addCharacter"), &GodotJolt::addCharacter);
    ClassDB::bind_method(D_METHOD("update"), &GodotJolt::update);    
}

GodotJolt::GodotJolt(){
    JPH::PhysicsSystem* phisicsSystem = new JPH::PhysicsSystem();
    firstPhysicsManager = memnew(FirstPhysicsManager());
}

void GodotJolt::addCharacter(){
    firstPhysicsManager->addCharacter();
}

void GodotJolt::update(){
    firstPhysicsManager->update();
}
