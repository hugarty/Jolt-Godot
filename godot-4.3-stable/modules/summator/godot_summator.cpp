/* summator.cpp */

#include "godot_summator.h"
#include <Summator.h>


int GodotSummator::add(int p_value, int b_value) {
	return instance.doSum(p_value,b_value);
}

int GodotSummator::wrongAdd(int p_value, int b_value) {
	return instance.doIncorrectSum(p_value, b_value);
}

void GodotSummator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add", "p_value", "b_value"), &GodotSummator::add);
	ClassDB::bind_method(D_METHOD("wrongAdd", "p_value", "b_value"), &GodotSummator::wrongAdd);
}

GodotSummator::GodotSummator() {
	instance = Summator();
}