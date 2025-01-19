/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "mmoFilho.h"

void initialize_mmo_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    ClassDB::register_class<MMOFilho>();
}

void uninitialize_mmo_module(ModuleInitializationLevel p_level) {
	// Nothing to do here in this example.
}