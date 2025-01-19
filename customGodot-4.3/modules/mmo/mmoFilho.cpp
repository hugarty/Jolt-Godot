
#include "core/object/ref_counted.h"
#include "mmoFilho.h"


void MMOFilho::_bind_methods() {
	// ADD_SIGNAL(MethodInfo("damageRecieved"));
	// ADD_SIGNAL(MethodInfo("rawDamageRecieved"));
	// ADD_SIGNAL(MethodInfo("cureRecieved"));
	// ADD_SIGNAL(MethodInfo("cureApplied"));
	// ADD_SIGNAL(MethodInfo("shieldRecieved"));
	// ADD_SIGNAL(MethodInfo("shieldRemoved"));
    
    // TODO - add signal para as outras interações  
    // TODO - add signal para as outras interações  
    // TODO - add signal para as outras interações  
    // TODO - add signal para as outras interações  
    // TODO - add signal para as outras interações  
    // TODO - add signal para as outras interações  

    // ClassDB::bind_static_method("GDUnidade", D_METHOD("getNewInstance", "hp","armor","armorP","damage"), &GDUnidade::getNewInstance);

    // ClassDB::bind_method(D_METHOD("recieveDamage", "damageInfo"), &GDUnidade::recieveDamage);
    // ClassDB::bind_method(D_METHOD("addToChangeDamageRecieved", "changeDamage"), &MMOFilho::addToChangeDamageRecieved);

    ClassDB::bind_method(D_METHOD("addCharacter"), &MMOFilho::addCharacter);
    // ClassDB::bind_method(D_METHOD("getCharacterPosition"), &MMOFilho::getCharacterPosition);
    ClassDB::bind_method(D_METHOD("update"), &MMOFilho::update);    
}


MMOFilho::MMOFilho(){
    JPH::PhysicsSystem* phisicsSystem = new JPH::PhysicsSystem();
    firstPhysicsManager = memnew(FirstPhysicsManager());
}

void MMOFilho::addCharacter(){
    firstPhysicsManager->addCharacter();
}

// void MMOFilho::getCharacterPosition(){
//     // firstPhysicsManager->getCharacterPosition();
// }

void MMOFilho::update(){
    firstPhysicsManager->update();
}

//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src/
//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src/
//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src
//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src/Jolt/
//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src/Jolt/
//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src/Jolt/
//   /home/hpca/xdev/development/mmo-godot-4.3/modules/mmo/src/Build/Linux_Debug/_deps/joltphysics-src/Jolt/

 
// GDUnidade* GDUnidade::getNewInstance (const int& hp, const int& armor, const int& armorP, const int& damage) {
//     return memnew(GDUnidade(hp, armor, armorP, damage));
// }

// GDUnidade::GDUnidade() {
//     unidade_ = memnew(LibUnidade(10));
// }

// GDUnidade::GDUnidade(int hp, int armor, int armorP, int damage) {
//     unidade_ = memnew(LibUnidade(hp, armor, armorP, damage));
// }

// void GDUnidade::addShield (int shield) {
//     unidade_->addShield(shield);
//     emit_signal(SNAME("shieldRecieved"), shield);
// }

// void GDUnidade::removeShield() {
//     int shieldBeforeRemove = unidade_->getShield();
//     unidade_->removeShield();
//     emit_signal(SNAME("shieldRemoved"), shieldBeforeRemove);
// }

    
// void GDUnidade::addToChangeDamageRecieved (Ref<GDChangeDamage> changeDamage) {
//     ChangeDamage* changeDamage_ = changeDamage->getChangeDamage();
//     unidade_->addToChangeDamageRecieved(*changeDamage_);
// }

















