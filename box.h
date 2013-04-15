#ifndef BOX_H
#define BOX_H

#include "cvec.h"
#include "object.h"
#include "ray.h"

#define BOX 4

class Box : public Object {
public:
	Box();
	Box(const Cvec3f &min_, const Cvec3f &max_) : minPoint(min_), maxPoint(max_) {};
	int getType() {
		return BOX;
	}
	Cvec3f &getMinPoint() {
		return minPoint;
	}
	Cvec3f &getMaxPoint() {
		return maxPoint;
	}
	Cvec3f getNormal(Cvec3f &intersectionPoint);
	int intersect(Ray &ray, double &root);

private:
	Cvec3f minPoint;
	Cvec3f maxPoint;	
};

#endif