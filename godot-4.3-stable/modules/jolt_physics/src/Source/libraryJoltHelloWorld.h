#ifndef FIRST_PHYSICS_MANAGER_H
#define FIRST_PHYSICS_MANAGER_H


#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Body/BodyManager.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>


// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>
#include <chrono>

class FirstPhysicsManager {

public:
    FirstPhysicsManager();
    ~FirstPhysicsManager();

    void addCharacter();
    JPH::Vec3 getCharacterPosition();

    void update();


    JPH::PhysicsSystem physics_system;

    // // The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
	// // variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
    // BodyInterface& body_interface;

	// The 'player' character
	JPH::Ref<JPH::CharacterVirtual> mCharacter;

	// We need a temp allocator for temporary allocations during the physics update. We're
	// pre-allocating 10 MB to avoid having to do allocations during the physics update.#include <glm/gtc/type_ptr.hpp>
	// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
	// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
	// malloc / free.
	JPH::TempAllocatorImpl* temp_allocator;

    // We need a job system that will execute physics jobs on multiple threads. Typically
	// you would implement the JobSystem interface yourself and let Jolt Physics run on top
	// of your own job scheduler. JobSystemThreadPool is an example implementation.
    JPH::JobSystemThreadPool* job_system;

};


#endif