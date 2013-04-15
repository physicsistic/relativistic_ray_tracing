#ifndef MATERIAL_H
#define MATERIAL_H

#include "cvec.h"

typedef Cvec3f Color;

class Material {
public:
	Material();

	// Color methods
	void setColor(Color &color_) {
		color = color_;
	}
	void setColor(double r, double g, double b) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
	Color getColor() {
		return color;
	}

	// Diffusion reflection methods
	void setDiffuse(double diffuse_) {
		diffuse = diffuse_;
	}
	double getDiffuse() {
		return diffuse;
	}

	// Reflection methods
	void setReflection(double reflection_) {
		reflection = reflection_;
	}
	double getReflection() {
		return reflection;
	}

	// Refraction methods
	void setRefraction(double refraction_) {
		refraction = refraction_;
	}
	void setRefractionIndex(double refractionIndex_) {
		refractionIndex = refractionIndex_;
	}
	double getRefraction() {
		return refraction;
	}
	double getRefractionIndex() {
		return refractionIndex;
	}

	// Specular methods
	void setSpecular(double specular_) {
		specular = specular_;
	}
	double getSpecular() {
		return specular;
	}


private:
	Color color;
	double diffuse;
	double reflection;
	double refraction;
	double refractionIndex;
	double specular;
};
#endif