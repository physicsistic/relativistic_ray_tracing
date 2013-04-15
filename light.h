#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include "cvec.h"
#include "material.h"

using namespace std;

#define LIGHT 3

class Light {

public:
	Light();
	Light(const Cvec3f &center_) : center(center_) {};

	void setName(string name_);
	string getName() {
		return name;
	}

	void setType(int type_) {
		type = type_;
	}
	int &getType() {
		return type;
	}

	void setRadius(double radius_) {
		radius = radius_;
	}
	double &getRadius() {
		return radius;
	}

	void setCenter(const Cvec3f &center_) {
		center = center_;
	}
	Cvec3f &getCenter() {
		return center;
	}
	
	void setMaterial(Material &material_) {
		material = material_;
	}
	Material *getMaterial() {
		return &material;
	}

protected:
	Material material;

private:
	Cvec3f center;
	string name;
	double radius;
	int type; // 0 = point light, 1 = circular area light
};

#endif