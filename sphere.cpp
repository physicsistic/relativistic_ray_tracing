#include "sphere.h"

using namespace std;

Sphere::Sphere() {
	center = Cvec3f(0.0, 0.0, 0.0);
	radius = 1.0;
	radiusSquare = 1.0;
	radiusInverse = 1.0;
}

int Sphere::intersect(Ray &ray, double &root) {
	Cvec3f centerToOrigin = center - ray.getOrigin();
	double b = dot(centerToOrigin, ray.getDirection());
	double D = b * b - dot(centerToOrigin, centerToOrigin) + radiusSquare;
	int returnValue = 0;
	if (D > 0) {
		double d = sqrt(D);
		double root1 = b - d;
		double root2 = b + d;

		if (root2 > 0) {
			if (root1 < 0) { // we are inside the sphere
				if (root2 < root) { 
					root = root2;
					returnValue = -1;
				}
			}
			else {
				if (root1 < root) {
					root = root1;
					returnValue = 1;
				}
			}
		}
	}
	return returnValue;
}