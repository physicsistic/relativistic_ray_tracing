#ifndef PLANE_H
#define PLANE_H

#include "cvec.h"
#include "object.h"
#include "ray.h"

#define PLANE 2

class Plane : public Object {
public:
	Plane();
	Plane(const Cvec3f &normal_, double Q_) : 
		normal(normal_), 
		Q(Q_) {};

	int getType() {
		return PLANE;
	}
	Cvec3f getNormal(Cvec3f &position_) {
		return normal;
	}
	double &getQ() {
		return Q;
	}
	int intersect(Ray &ray, double &dist);

private:
	Cvec3f normal;
	double Q; // Q is the dot product of the normal vector and a point on the plane
};

#endif