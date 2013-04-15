#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "cvec.h"
#include "object.h"

#define SPHERE 1

class Sphere : public Object {
public:
	// Constructor
	Sphere ();
	Sphere (const Cvec3f &center_, double radius_) :
		center(center_), 
		radius(radius_), 
		radiusSquare(radius_ * radius_),
		radiusInverse(1.0 / radius_) {};
	// Accessor
	int getType() { 
		return SPHERE; 
	}
	Cvec3f &getCenter() { 
		return center; 
	}
	double getRadius() { 
		return radius; 
	}
	double getRadiusSquare() { 
		return radiusSquare; 
	}
	Cvec3f getNormal(Cvec3f &position_) {
		return (position_ - center) * radiusInverse;
	}
	int intersect(Ray &ray, double &root);

private:
	Cvec3f center;
	double radius, radiusSquare, radiusInverse;
};

#endif