#include "material.h"

Material::Material() {
	color = Color(0.2, 0.2, 0.2);
	diffuse = 0.2;
	reflection = 0.0;
	refraction = 0.0;
	refractionIndex = 0.0;
	specular = 0.0;
}