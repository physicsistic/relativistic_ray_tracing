#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "cvec.h"
#include "ray.h"
#include "material.h"

using namespace std;

class Object {

public:
	Object(): name("\0") {};
	void setName(string name_);
	string getName() {
		return name;
	}

	void setMaterial(Material &material_) {
		material = material_;
	}
	Material *getMaterial() {
		return &material;
	}

	virtual int getType() = 0;
	virtual int intersect(Ray &ray, double &root) = 0;
	virtual Cvec3f getNormal(Cvec3f &position) = 0;

protected:
	Material material;
private:
	string name;
};
#endif