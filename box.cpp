#include <cmath>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

#include "box.h"

using namespace std;

Box::Box() {
	minPoint = Cvec3f(0.0, 0.0, 0.0);
	maxPoint = Cvec3f(1.0, 1.0, 1.0);
}

int Box::intersect(Ray &ray, double &root) {
	double tmp, tnear=-1.0e6, tfar=1.0e6;
  
  Cvec3f tmin = (minPoint - ray.getOrigin()) / ray.getDirection();;
  Cvec3f tmax = (maxPoint - ray.getOrigin()) / ray.getDirection();;

  if(tmin[0] > tmax[0]) { 
  	tmp=tmin[0]; 
  	tmin[0]=tmax[0]; 
  	tmax[0]=tmp;
  }
  if(tmin[1] > tmax[1]) { 
  	tmp=tmin[1]; 
  	tmin[1]=tmax[1]; 
  	tmax[1]=tmp;
  }
  if(tmin[2] > tmax[2]) { 
  	tmp=tmin[2]; 
  	tmin[2]=tmax[2]; 
  	tmax[2]=tmp;
  }

  tnear = max(tmin[2], max(tmin[1], max(tmin[0], (float) tnear)));
  tfar = min(tmax[2], min(tmax[1], min(tmax[0], (float) tfar)));

  // Ray missed the box
  if(tnear > tfar) 
  	return 0;
  // Box behind viewpoint
  if(tfar < 0) 
  	return 0; 

  // Box contain viewpoint
  if(tnear<0) { 
  	root=tfar; 
  	return -1; 
  }

  root = tnear;
  return 1;
}

Cvec3f Box::getNormal(Cvec3f &intersectionPoint) {

	Cvec3f distance = minPoint - intersectionPoint;
	double minDistance = abs(distance[0]);
	int side = 0;
	if(abs(distance[1]) < minDistance) {
		minDistance = abs(distance[1]);
		side = 2;
	}
	if(abs(distance[2]) < minDistance) {
		minDistance = abs(distance[2]);
		side = 4;
	}
	distance = maxPoint - intersectionPoint;
	if(abs(distance[0]) < minDistance) {
		minDistance = abs(distance[0]);
		side = 1;
	}
	if(abs(distance[1]) < minDistance) {
		minDistance = abs(distance[1]);
		side = 3;
	}
	if(abs(distance[2]) < minDistance) {
		minDistance = abs(distance[2]);
		side = 5;
	}

	if(side == 0)
		return Cvec3f(-1., 0., 0.);
	if(side == 1)
		return Cvec3f( 1., 0., 0.);
	if(side == 2)
		return Cvec3f( 0.,-1., 0.);
	if(side == 3)
		return Cvec3f( 0., 1., 0.);
	if(side == 4)
		return Cvec3f( 0., 0., -1.);
	return Cvec3f(0., 0., 1.);
}