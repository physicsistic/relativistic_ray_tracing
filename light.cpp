#include "light.h"

Light::Light() {
	center = Cvec3f(0., 0., 0.);
	radius = 1.0;
	type = 0;
}

void Light::setName(string name_) {
	name.assign(name_);
}