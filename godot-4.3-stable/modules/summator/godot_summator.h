/* summator.h */

#ifndef GODOT_SUMMATOR_H
#define GODOT_SUMMATOR_H

#include "core/object/ref_counted.h"
#include <Summator.h>

class GodotSummator : public RefCounted {
	GDCLASS(GodotSummator, RefCounted);

	Summator instance;
	int count;

protected:
	static void _bind_methods();

public:
	int add(int p_value, int b_value);
    int wrongAdd(int p_value, int b_value);

	GodotSummator();
};

#endif // SUMMATOR_H