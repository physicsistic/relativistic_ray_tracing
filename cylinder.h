#ifndef CYLINDER_H
#define CYLINDER_H

#include "cvec.h"
#include "object.h"
#include "ray.h"

#define CYLINDER 5

class Cylinder : public Object {

public:
	Cylinder();
	Cylinder(const Cvec3f &top_, const Cvec3f &bottom_, double radius_) :
		top(top_), bottom(bottom_), radius(radius_), radiusSquare(radius_ * radius_),
		center(Cvec3f((top_[0] + bottom_[0]) * 0.5, (top_[1] + bottom_[1]) * 0.5, (top_[2] + bottom_[2]) * 0.5)) {};

	int getType() {
		return CYLINDER;
	}
	Cvec3f getTop() {
		return top;
	}
	Cvec3f getBottom() {
		return bottom;
	}
	Cvec3f getCenter() {
		return center;
	}
	double getRadius() {
		return radius;
	}
	Cvec3f getVector() {
		return (top - bottom);
	}
	Cvec3f getNormal(Cvec3f &position);
	int intersect(Ray &ray, double &root);

private:
	Cvec3f top;
	Cvec3f bottom;
	Cvec3f center;
	double radius;
	double radiusSquare;
};

#endif