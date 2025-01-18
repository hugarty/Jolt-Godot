
#include "libraryJoltHelloWorld.h"

JPH_SUPPRESS_WARNINGS

// If you want your code to compile using single or double precision write 0.0_r to get a Real value that compiles to double or float depending if JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;

// We're also using STL classes in this example
using namespace std;

// Callback for traces, connect this to your own trace function if you have one
static void TraceImpl(const char *inFMT, ...)
{
	// Format the message
	va_list list;
	va_start(list, inFMT);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), inFMT, list);
	va_end(list);

	// Print to the TTY
	std::cout << buffer << endl;
}

#ifdef JPH_ENABLE_ASSERTS

// Callback for asserts, connect this to your own assert handler if you have one
static bool AssertFailedImpl(const char *inExpression, const char *inMessage, const char *inFile, uint inLine)
{
	// Print to the TTY
	cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << endl;

	// Breakpoint
	return true;
};

#endif // JPH_ENABLE_ASSERTS

// Layer that objects can be in, determines which other objects it can collide with
// Typically you at least want to have 1 layer for moving bodies and 1 layer for static bodies, but you can have more
// layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics simulation
// but only if you do collision testing).
namespace Layers
{
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 1;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
};

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
	virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override
	{
		switch (inObject1)
		{
		case Layers::NON_MOVING:
			return inObject2 == Layers::MOVING; // Non moving only collides with moving
		case Layers::MOVING:
			return true; // Moving collides with everything
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

// Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
// You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
// your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
namespace BroadPhaseLayers
{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr uint NUM_LAYERS(2);
};

// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:
	BPLayerInterfaceImpl()
	{
		// Create a mapping table from object to broad phase layer
		mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
		mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
	}

	virtual uint GetNumBroadPhaseLayers() const override
	{
		return BroadPhaseLayers::NUM_LAYERS;
	}

	virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
	{
		JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
		return mObjectToBroadPhase[inLayer];
	}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	virtual const char *GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override
	{
		switch ((JPH::BroadPhaseLayer::Type)inLayer)
		{
		case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
			return "NON_MOVING";
		case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
			return "MOVING";
		default:
			JPH_ASSERT(false);
			return "INVALID";
		}
	}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

private:
	JPH::BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
	virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
	{
		switch (inLayer1)
		{
		case Layers::NON_MOVING:
			return inLayer2 == BroadPhaseLayers::MOVING;
		case Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

// An example contact listener
class MyContactListener : public JPH::ContactListener
{
public:
	// See: ContactListener
	virtual JPH::ValidateResult OnContactValidate(const JPH::Body &inBody1, const JPH::Body &inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult &inCollisionResult) override
	{
		cout << "Contact validate callback" << endl;

		// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
		return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
	}

	virtual void OnContactAdded(const JPH::Body &inBody1, const JPH::Body &inBody2, const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override
	{
		cout << "A contact was added" << endl;
	}

	virtual void OnContactPersisted(const JPH::Body &inBody1, const JPH::Body &inBody2, const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override
	{
		cout << "A contact was persisted" << endl;
	}

	virtual void OnContactRemoved(const JPH::SubShapeIDPair &inSubShapePair) override
	{
		cout << "A contact was removed" << endl;
	}
};

// An example activation listener
class MyBodyActivationListener : public JPH::BodyActivationListener
{
public:
	virtual void OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override
	{
		cout << "A JPH::Body got activated" << endl;
	}

	virtual void OnBodyDeactivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override
	{
		cout << "A JPH::Body went to sleep" << endl;
	}
};


// ---------------------------------------

FirstPhysicsManager::FirstPhysicsManager(){
	// Register allocation hook. In this example we'll just let Jolt use malloc / free but you can override these if you want (see Memory.h).
	// This needs to be done before any other Jolt function is called.
	JPH::RegisterDefaultAllocator();

	// Install trace and assert callbacks
	JPH::Trace = TraceImpl;
	JPH::JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

	// Create a factory, this class is responsible for creating instances of classes based on their name or hash and is mainly used for deserialization of saved data.
	// It is not directly used in this example but still required.
	JPH::Factory::sInstance = new JPH::Factory();

	// Register all physics types with the factory and install their collision handlers with the CollisionDispatch class.
	// If you have your own custom shape types you probably need to register their handlers with the CollisionDispatch before calling this function.
	// If you implement your own default material (PhysicsMaterial::sDefault) make sure to initialize it before this function or else this function will create one for you.
	JPH::RegisterTypes();

	// We need a temp allocator for temporary allocations during the physics update. We're
	// pre-allocating 10 MB to avoid having to do allocations during the physics update.#include <glm/gtc/type_ptr.hpp>
	// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
	// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
	// malloc / free.
    temp_allocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);

	// We need a job system that will execute physics jobs on multiple threads. Typically
	// you would implement the JobSystem interface yourself and let Jolt Physics run on top
	// of your own job scheduler. JobSystemThreadPool is an example implementation.
    job_system = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

	// This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll get an error.
	// Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
	const uint cMaxBodies = 1024;

	// This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
	const uint cNumBodyMutexes = 0;

	// This is the max amount of JPH::Body pairs that can be queued at any time (the broad phase will detect overlapping
	// JPH::Body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make this buffer
	// too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This is slightly less efficient.
	// Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
	const uint cMaxBodyPairs = 1024;

	// This is the maximum size of the contact constraint buffer. If more contacts (collisions between bodies) are detected than this
	// number then these contacts will be ignored and bodies will start interpenetrating / fall through the world.
	// Note: This value is low because this is a simple test. For a real project use something in the order of 10240.
	const uint cMaxContactConstraints = 1024;

	// Create mapping table from object layer to broadphase layer
	// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
	// Also have a look at BroadPhaseLayerInterfaceTable or BroadPhaseLayerInterfaceMask for a simpler interface.
	BPLayerInterfaceImpl broad_phase_layer_interface;

	// Create class that filters object vs broadphase layers
	// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
	// Also have a look at ObjectVsBroadPhaseLayerFilterTable or ObjectVsBroadPhaseLayerFilterMask for a simpler interface.
	ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;

	// Create class that filters object vs object layers
	// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
	// Also have a look at ObjectLayerPairFilterTable or ObjectLayerPairFilterMask for a simpler interface.
	ObjectLayerPairFilterImpl object_vs_object_layer_filter;

	// Now we can create the actual physics system.
	physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

	// A JPH::Body activation listener gets notified when bodies activate and go to sleep
	// Note that this is called from a job so whatever you do here needs to be thread safe.
	// Registering one is entirely optional.
	MyBodyActivationListener body_activation_listener;
	physics_system.SetBodyActivationListener(&body_activation_listener);

	// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
	// Note that this is called from a job so whatever you do here needs to be thread safe.
	// Registering one is entirely optional.
	MyContactListener contact_listener;
	physics_system.SetContactListener(&contact_listener);

	// The main way to interact with the bodies in the physics system is through the JPH::Body interface. There is a locking and a non-locking
	// variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
	// body_interface = physics_system.GetBodyInterface();

	// Next we can create a rigid JPH::Body to serve as the floor, we make a large box
	// Create the settings for the collision volume (the shape).
	// Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
	JPH::BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 1.0f, 100.0f));
	floor_shape_settings.SetEmbedded(); // A ref counted object on the stack (base class RefTarget) should be marked as such to prevent it from being freed when its reference count goes to 0.

	// Create the shape
	JPH::ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
	JPH::ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

	// Create the settings for the JPH::Body itself. Note that here you can also set other properties like the restitution / friction.
	JPH::BodyCreationSettings floor_settings(floor_shape, JPH::RVec3(0.0_r, -1.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);

	// Create the actual rigid JPH::Body
	JPH::Body *floor = physics_system.GetBodyInterface().CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr
	floor->SetFriction(300.0f);
	// Add it to the world
	physics_system.GetBodyInterface().AddBody(floor->GetID(), JPH::EActivation::DontActivate);
}

FirstPhysicsManager::~FirstPhysicsManager(){

	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	//!!!! physics_system.GetBodyInterface().RemoveBody(sphere_id);

	// Destroy the sphere. After this the sphere ID is no longer valid.
	//!!!! body_interface.DestroyBody(sphere_id);

	// Remove and destroy the floor
	//!!!! body_interface.RemoveBody(floor->GetID());
	//!!!! body_interface.DestroyBody(floor->GetID());

	// Unregisters all types with the factory and cleans up the default material
	JPH::UnregisterTypes();

	// Destroy the factory
	delete JPH::Factory::sInstance;
	JPH::Factory::sInstance = nullptr;

}

void FirstPhysicsManager::addCharacter(){

	JPH::EBackFaceMode sBackFaceMode = JPH::EBackFaceMode::CollideWithBackFaces;
	// float		sUpRotationX = 0;
	// float		sUpRotationZ = 0;
	float		sMaxSlopeAngle = JPH::DegreesToRadians(45.0f);
	float		sMaxStrength = 100.0f;
	float		sCharacterPadding = 0.02f;
	float		sPenetrationRecoverySpeed = 1.0f;
	float		sPredictiveContactDistance = 0.1f;
	// bool		sEnableWalkStairs = true;
	// bool		sEnableStickToFloor = true;
	bool		sEnhancedInternalEdgeRemoval = false;
	bool		sCreateInnerBody = false;
	// bool		sPlayerCanPushOtherCharacters = true;
	// bool		sOtherCharactersCanPushPlayer = true;
	float	cCharacterHeightStanding = 1.35f;
	float	cCharacterRadiusStanding = 0.3f;
	// float	cCharacterHeightCrouching = 0.8f;
	// float	cCharacterRadiusCrouching = 0.3f;
	float	cInnerShapeFraction = 0.9f;
	JPH::RefConst<JPH::Shape>			mStandingShape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0.5f * cCharacterHeightStanding + cCharacterRadiusStanding, 0), JPH::Quat::sIdentity(), new JPH::CapsuleShape(0.5f * cCharacterHeightStanding, cCharacterRadiusStanding)).Create().Get();
	JPH::RefConst<JPH::Shape>			mInnerStandingShape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0.5f * cCharacterHeightStanding + cCharacterRadiusStanding, 0), JPH::Quat::sIdentity(), new JPH::CapsuleShape(0.5f * cInnerShapeFraction * cCharacterHeightStanding, cInnerShapeFraction * cCharacterRadiusStanding)).Create().Get();

	JPH::Ref<JPH::CharacterVirtualSettings> settings = new JPH::CharacterVirtualSettings();
	settings->mMaxSlopeAngle = sMaxSlopeAngle;
	settings->mMaxStrength = sMaxStrength;
	settings->mShape = mStandingShape;
	settings->mBackFaceMode = sBackFaceMode;
	settings->mCharacterPadding = sCharacterPadding;
	settings->mPenetrationRecoverySpeed = sPenetrationRecoverySpeed;
	settings->mPredictiveContactDistance = sPredictiveContactDistance;
	settings->mSupportingVolume = JPH::Plane(JPH::Vec3::sAxisY(), -cCharacterRadiusStanding); // Accept contacts that touch the lower sphere of the capsule
	settings->mEnhancedInternalEdgeRemoval = sEnhancedInternalEdgeRemoval;
	settings->mInnerBodyShape = sCreateInnerBody? mInnerStandingShape : nullptr;
	settings->mInnerBodyLayer = Layers::MOVING;

	// List of active characters in the scene so they can collide
	JPH::CharacterVsCharacterCollisionSimple mCharacterVsCharacterCollision;
	JPH::Vec3 initialCharacterPosition = JPH::Vec3(-1.5f, 0.0f, 1.5f);
	mCharacter = new JPH::CharacterVirtual(settings, initialCharacterPosition, JPH::Quat::sIdentity(), 0, &physics_system);
	mCharacter->SetCharacterVsCharacterCollision(&mCharacterVsCharacterCollision);
	mCharacterVsCharacterCollision.Add(mCharacter);

    mCharacter->SetLinearVelocity(JPH::Vec3(1.0f, 0.0f, 1.0f));

}

JPH::Vec3 FirstPhysicsManager::getCharacterPosition(){
    return mCharacter->GetPosition();
}

void FirstPhysicsManager::update(){
        // We simulate the physics world in discrete time steps. 60 Hz is a good rate to update the physics system.
        const float cDeltaTime = 1.0f / 60.0f;
        		// If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
		const int cCollisionSteps = 1;

		// Step the world
		physics_system.Update(cDeltaTime, cCollisionSteps, temp_allocator, job_system);

		JPH::CharacterVirtual::ExtendedUpdateSettings update_settings;
		mCharacter->ExtendedUpdate(
			cDeltaTime,
			-mCharacter->GetUp() * physics_system.GetGravity().Length(),
			update_settings,
			physics_system.GetDefaultBroadPhaseLayerFilter(Layers::MOVING),
			physics_system.GetDefaultLayerFilter(Layers::MOVING),
			{ },
			{ },
			*temp_allocator
		);
}
