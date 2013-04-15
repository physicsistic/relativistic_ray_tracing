#include <stdio.h>
#include <cstdlib>
#include <cstring>

#include "scene.h"

using namespace std;

int getLine(FILE *input, char *line) {
	char buffer[80];
	fgets(buffer, 80, input);
	if (strncmp (buffer, "#", 1) == 0) {
		fgets(buffer, 80, input);
	}
	strncpy(line, buffer, 80);
	return 0;
}

Scene::~Scene() {
	numObjects = 0;
	numLights = 0;
	delete lights;
	delete objects;
}

void Scene::initialize() {
	int n = 0; 
	int objectNumber = 0;
	int lightNumber = 0;
	float a, b, c, d, e, f, g;

	char line[80], name[80];

	// open input scene.txt for the initialization process
	FILE *input = fopen("scene.txt", "r");
	if (!input) {
		printf("Scene::initialization(): Error reading %s\n", "scene.txt");
		exit(-1);
	}

	while(!feof(input)) {
		fgets(line, 80, input);
		if (strncmp(line, "PLANE", 5) == 0) {
			objectNumber++;
		}
		if (strncmp(line, "SPHERE", 6) == 0) {
			objectNumber++;
		}
		if (strncmp(line, "LIGHT", 5) == 0) {
			lightNumber++;
		}
		if (strncmp(line, "BOX", 3) == 0) {
			objectNumber++;
		}
		if (strncmp(line, "CYLINDER", 8) == 0) {
			objectNumber++;
		}
	}
	objects = new Object *[objectNumber];
	lights = new Light *[lightNumber];
	numObjects = objectNumber;
	numLights = lightNumber;
	printf("Number of Objects: %d\n", objectNumber);
	printf("Number of Lights: %d\n", lightNumber);

	rewind(input);
	objectNumber = 0;
	lightNumber = 0;

	while (!feof(input)) {
		n = 0;
		strcpy(name, "");
		fgets(line, 80, input);
		if(strncmp(line, "#", 1) == 0) {
			n = 0;
		}
		if(strncmp(line, "PLANE", 5) == 0) {
			n = 1;
		}
		if(strncmp(line, "SPHERE", 6) == 0) {
			n = 2;
		}
		if(strncmp(line, "LIGHT", 5) == 0) {
			n = 3;
		}
		if(strncmp(line, "BOX", 3) == 0) {
			n = 4;
		}
		if(strncmp(line, "CYLINDER", 8) == 0) {
			n = 5;
		}
		switch (n) {
		  case 0:
		    break;
		  case 1:
		  	// name
		    getLine(input, line);
		    strcpy(name, line);
		    // vector
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    // position
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber] = new Plane(Cvec3f(a, b, c), d);
		    objects[objectNumber]->setName(name);
		    // diffuse value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setDiffuse(d);
		    // specular value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setSpecular(d);
		    // reflection value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setReflection(d);
		    // refraction value
		    getLine(input, line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setRefraction(d);
		    // refraction index value
		    if (d > 0.0) {
		    	getLine(input, line);
		    	sscanf(line, "%f", &d);
		    	objects[objectNumber]->getMaterial()->setRefractionIndex(d);
		    }
		    // color value
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    objects[objectNumber]->getMaterial()->setColor(a, b, c);
		    objectNumber++;
		    break;
		  case 2:
		  	// name
		    getLine(input, line);
		    strcpy(name,line);
		    // position
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    // radius
		    getLine(input, line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber] = new Sphere(Cvec3f(a, b, c), d);
		    objects[objectNumber]->setName(name);
		    // diffuse value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setDiffuse(d);
		    // specular value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setSpecular(d);
		    // reflection value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setReflection(d);
		    // refraction value
		    getLine(input, line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setRefraction(d);
		    // refraction index value
		    if (d > 0.0) {
		    	getLine(input, line);
		    	sscanf(line, "%f", &d);
		    	objects[objectNumber]->getMaterial()->setRefractionIndex(d);
		    }
		    // color
		    getLine(input,line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    objects[objectNumber]->getMaterial()->setColor(a, b, c);
		    objectNumber++;
		    break;
		  case 3:
		  	// name
		    getLine(input, line);
		    strcpy(name, line);
		    // position
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    lights[lightNumber] = new Light(Cvec3f(a, b, c));
		    lights[lightNumber]->setName(name);
		    // color
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    lights[lightNumber]->getMaterial()->setColor(a, b, c);
		    lightNumber++;
		    break;
		  case 4:
		  	// name
		    getLine(input, line);
		    strcpy(name,line);
		    // min
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    // max
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &d, &e, &f);
		    objects[objectNumber] = new Box(Cvec3f(a, b, c), Cvec3f(d, e, f));
		    objects[objectNumber]->setName(name);
		    // diffuse value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setDiffuse(d);
		    // specular value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setSpecular(d);
		    // reflection value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setReflection(d);
		    // refraction value
		    getLine(input, line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setRefraction(d);
		    // refraction index value
		    if (d > 0.0) {
		    	getLine(input, line);
		    	sscanf(line, "%f", &d);
		    	objects[objectNumber]->getMaterial()->setRefractionIndex(d);
		    }
		    // color
		    getLine(input,line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    objects[objectNumber]->getMaterial()->setColor(a, b, c);
		    objectNumber++;
		    printf("Added a box...\n");
		    break;
		  case 5:
		  	// name
		    getLine(input, line);
		    strcpy(name,line);
		    // top
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    // bottom
		    getLine(input, line);
		    sscanf(line, "%f %f %f", &d, &e, &f);
		    // radius
		    getLine(input, line);
		    sscanf(line, "%f", &g);
		    objects[objectNumber] = new Cylinder(Cvec3f(a, b, c), Cvec3f(d, e, f), g);
		    objects[objectNumber]->setName(name);
		    // diffuse value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setDiffuse(d);
		    // specular value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setSpecular(d);
		    // reflection value
		    getLine(input,line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setReflection(d);
		    // refraction value
		    getLine(input, line);
		    sscanf(line, "%f", &d);
		    objects[objectNumber]->getMaterial()->setRefraction(d);
		    // refraction index value
		    if (d > 0.0) {
		    	getLine(input, line);
		    	sscanf(line, "%f", &d);
		    	objects[objectNumber]->getMaterial()->setRefractionIndex(d);
		    }
		    // color
		    getLine(input,line);
		    sscanf(line, "%f %f %f", &a, &b, &c);
		    objects[objectNumber]->getMaterial()->setColor(a, b, c);
		    objectNumber++;
		    printf("Added a cylinder...\n");
		    break;
		  default:
		    break;
			}
		}
}