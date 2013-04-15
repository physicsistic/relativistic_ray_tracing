#include "ray.h"

Ray::Ray() {
	origin = Cvec3f(0., 0., 0.);
	direction = Cvec3f(0., 0., 0.);
}

Ray::Ray(const Cvec3f &origin_, Cvec3f &direction_) {
	origin = origin_;
	direction = direction_;
}