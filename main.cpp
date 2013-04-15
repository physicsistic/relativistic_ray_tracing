#include <iostream>
#include <GL/glew.h>
#include <GLUT/glut.h>

#include "cvec.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "scene.h"
#include "material.h"
#include "box.h"
#include "cylinder.h"

using namespace std;

#define EPSILON 0.01
#define maxRayTraceDepth 10

static int width = 800;
static int height = 600;
static unsigned char *image_data = new unsigned char[width * height * 3];

Object *rayTrace(Ray &ray, Color &color, Scene &scene, int rayTraceDepth, double refractionIndex, double &distance);

// Refraction
int refraction (Ray &ray, Color &color, Object *object, Scene &scene, 
	Cvec3f &N, Cvec3f &pointOfIntersection, int depth, double &reflectionConstant,
	double refractionIndex0, double &distance, int &hit) {
	double refractionIndex = object->getMaterial()->getRefractionIndex();
	double n = refractionIndex0 / refractionIndex;
	Cvec3f N1 = N * hit;
	double cosThetaI = - dot(N1, ray.getDirection());
	double sinThetaI = sqrt(1.0 - cosThetaI * cosThetaI);
	double sinThetaT = n * sinThetaI;

	if (sinThetaT * sinThetaT < 1.0) {
		double cosThetaT = sqrt(1.0 - sinThetaT * sinThetaT);
		Cvec3f R4 = ray.getDirection() * n - N1 * (n * cosThetaI + cosThetaT);
		R4.normalize();
		Color refractedColor(0.0, 0.0, 0.0);
		double dist;
		Cvec3f R5 = pointOfIntersection + R4 * EPSILON;
		Ray R6 = Ray(R5, R4);
		rayTrace(R6, refractedColor, scene, depth + 1, refractionIndex, dist);
		// Beer's Law
		Color absorbance = object->getMaterial()->getColor() * 0.15 * dist * (-1.0);
		Color transparency = Color(exp(absorbance[0]), exp(absorbance[1]), exp(absorbance[2]));
		color += refractedColor * transparency;
	}
	return 0;
}

// Reflection
int reflection(Ray &ray, Color &color, Object *object, Scene &scene, Cvec3f &N,
	Cvec3f &pointOfIntersection, int depth, double &reflectionConstant, 
	double refractionIndex, double &distance) {
	Cvec3f R1 = ray.getDirection() - N * dot(ray.getDirection(), N) * 2.0;
	R1.normalize();
	Color reflectionColor(0., 0., 0.);
	Cvec3f R2 = pointOfIntersection + R1 * EPSILON;
	Ray R3 = Ray(R2, R1);
	rayTrace(R3, reflectionColor, scene, depth + 1, refractionIndex, distance);
	color += reflectionColor * object->getMaterial()->getColor() * reflectionConstant;
}

// Diffuse Shading
int diffuse(Ray &ray, Color &color, Object *object, Light *light, 
	Cvec3f &v, Cvec3f &n, double &cosTheta, double diffuseConstant) {
	Cvec3f diffuseIntensity;
	cosTheta = dot(n, v);
	if (cosTheta > 0.0) {
		diffuseIntensity = light->getMaterial()->getColor()*object->getMaterial()->getColor();
		color += diffuseIntensity * diffuseConstant * cosTheta;
	}
	return 0;
}

// Specular shading
int specular(Ray &ray, Color &color, Object *object, Light *light, Cvec3f &v,
	Cvec3f &n, double &cosTheta, double specularConstant) {
	double cosSigma;
	Cvec3f ve = ray.getDirection();
	Cvec3f vr = v - n * cosTheta * 2.0;
	Cvec3f specularIntensity = light->getMaterial()->getColor() * object->getMaterial()->getColor();
	cosSigma = dot(ve, vr);

	if (cosSigma > 0.) {
		color += specularIntensity * specularConstant * pow(cosSigma, 32);
	}
	return 0;
}

// Main Tracing Function
Object *rayTrace(Ray &ray, Color &color, Scene &scene, int rayTraceDepth,
	double refractionIndex, double &distance){
	double tempDistance = 1000000.0;
	Object *object = 0; 
	Object *testObject, *objectShadow;
	Light *light;
	double cosTheta;
	double diffuseConstant;
	double specularConstant;
	double reflectionConstant;
	double refractionConstant;
	double shadow;
	double magnitude;
	Cvec3f intersectionPoint, v, normal;
	Color diffuseIntensity;
	Ray shadowRay;
	int hit;

	distance = 1000000.0;
	if (rayTraceDepth > maxRayTraceDepth)
		return 0;

	for (int i = 0; i < scene.getNumObjects(); i++) {
		testObject = scene.getObject(i);
		int hitValue = testObject->intersect(ray, tempDistance);
		if (hitValue) {
			object = testObject;
			distance = tempDistance;
			hit = hitValue;
		}
	}
	// If no object is hit, return immediately.
	if (!object)
		return object;

	intersectionPoint = ray.getOrigin() + ray.getDirection() * distance;

	normal = object->getNormal(intersectionPoint);

// Shadowing
	for (int i = 0; i < scene.getNumLights(); i++) {
		light = scene.getLight(i);
		v = light->getCenter() - intersectionPoint;
		v.normalize();
		shadow = 1.0;
		shadowRay = Ray(intersectionPoint + v * EPSILON, v);

		for (int j = 0; j < scene.getNumObjects(); j++) {
			objectShadow = scene.getObject(j);
			magnitude = norm(v);
			if (objectShadow->intersect(shadowRay, magnitude))
				shadow = 0.0;
		}
		if (shadow > 0.0) {
			diffuseConstant = object->getMaterial()->getDiffuse();
			specularConstant = object->getMaterial()->getSpecular();
			if (diffuseConstant > 0.)
				diffuse(ray, color, object, light, v, normal, cosTheta, diffuseConstant);
			if (specularConstant > 0.)
				specular(ray, color, object, light, v, normal, cosTheta, specularConstant);
		}
	}

	//Reflection
	reflectionConstant = object->getMaterial()->getReflection();
	if (reflectionConstant > 0.0 && rayTraceDepth < maxRayTraceDepth)
		reflection(ray, color, object, scene, normal, intersectionPoint, rayTraceDepth, 
			reflectionConstant, refractionIndex, distance);
	
	refractionConstant = object->getMaterial()->getRefraction();
	if (refractionConstant > 0.0 && rayTraceDepth < maxRayTraceDepth)
		refraction(ray, color, object, scene, normal, intersectionPoint, rayTraceDepth, 
			refractionConstant, refractionIndex, distance, hit);
	return object;
}

//-----------------------------------------------------------------------------
// display Function
//-----------------------------------------------------------------------------
static void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

static void display() {
  float modelv[16];
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_FLAT);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, image_data);
  glutSwapBuffers();
}



void idle()
{
  glutPostRedisplay();
}

int main (int argc, char *argv[]) {
	double refractionIndex = 1.0;
	int depth = 1;
	int s = 5;
	double distance = 1000000.0;
	double invS = 1.0 / (double) (s - 1);
	Color color;
	Cvec3f viewPoint = Cvec3f(0.0, 10.0, -50.0), direction;
	Cvec3f lookAt = Cvec3f(-4.0, -1.0, 0.0);
	Ray ray;
	Object *object;

	Scene *scene = new Scene();
	scene[0].initialize();
	double beta = 0.75;
	cout << "Rendering...";
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			color = Cvec3f(0.0, 0.0, 0.0);
			for (int dy = -s/2; dy < (s+1)/2; dy++) {
				for (int dx = -s/2; dx < (s+1)/2; dx++) {
					double x = lookAt[0] + dx * invS / 100. + i / 100.;
					double y = lookAt[1] + dx * invS / 100. + j / 100.;
					double z = lookAt[2];
					double R = sqrt(x * x + y * y + z * z);
					double gamma = 1 / sqrt(1 - beta * beta);
					double z_transform = (lookAt[2] + beta * R) * gamma;
					direction = Cvec3f(x, y, z_transform) - viewPoint;
					direction.normalize();
					ray = Ray(viewPoint, direction);
					object = rayTrace(ray, color, scene[0], depth, refractionIndex, distance);
				}
			}
			int b = color[0] * 255 / (s * s);
			int g = color[1] * 255 / (s * s);
			int r = color[2] * 255 / (s * s);
			int index = j * width + i;
			if (r > 255) 
				r = 255;
			if (b > 255)
				b = 255;
			if (g > 255)
				g = 255;
			image_data[index * 3 + 0] = (unsigned char) b;
			image_data[index * 3 + 1] = (unsigned char) g;
			image_data[index * 3 + 2] = (unsigned char) r;
			if ((i % 50 == 0) && (j % 50 == 0))
				cout << ".";

		}
	}
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Raytracing");
  glutDisplayFunc(display);
  glutSetCursor(GLUT_CURSOR_NONE);
  glutIdleFunc(idle);
  glutMainLoop();

	delete scene;
	return 0;
}