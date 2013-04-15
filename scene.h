#ifndef SCENE_H
#define SCENE_H

#include "cvec.h"
#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include "light.h"
#include "object.h"
#include "material.h"
#include "box.h"
#include "cylinder.h"


class Scene {
public:
	Scene(): numObjects(0), objects(0), lights(0) {};
	~Scene();

	void initialize();

	int getNumObjects() const { 
		return numObjects; 
	}
	int getNumLights() const {
		return numLights;
	}

	Object *getObject(int index) { 
		return objects[index]; 
	}

	Light *getLight(int index) {
		return lights[index];
	}

private:
	int numObjects;
	int numLights;
	Object **objects;
	Light **lights;
};

#endif