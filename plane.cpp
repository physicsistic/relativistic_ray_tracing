#include <iostream>
#include "plane.h"

using namespace std;

// Default plane is a x-z plane passing through the origin
Plane::Plane() {
	normal = Cvec3f(0.0, 1.0, 0.0);
	Q = 0.0;
}

int Plane::intersect(Ray &ray, double &dist) {
	double rayNormal = dot(normal, ray.getDirection());

	if (rayNormal != 0.) {
		double distance = - (Q + dot(normal, ray.getOrigin())) / rayNormal;

		if (distance > 0.0) {
			if (distance < dist) {
				dist = distance;
				return 1;
			}
		}
	}
	return 0;
}