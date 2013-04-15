#include <cmath>
#include <iostream>

#include "cylinder.h"

using namespace std;

Cylinder::Cylinder() {
  top = Cvec3f(0.0, 2.0, 0.0);
  bottom = Cvec3f(0.0, 0.0, 0.0);
  center = Cvec3f(0.0, 1.0, 0.0);
  radius = 1.0;
  radiusSquare = 1.0;
}

int Cylinder::intersect(Ray &ray, double &root) {
  Cvec3f Rd = ray.getDirection();
  Cvec3f Ro = center - ray.getOrigin();
  Cvec3f intersectionPoint;
  double a = Rd[0]*Rd[0] + Rd[2]*Rd[2];
  double b = Ro[0]*Rd[0] + Ro[2]*Rd[2];
  double c = Ro[0]*Ro[0] + Ro[2]*Ro[2] - radiusSquare;
  double disc = b*b - a*c;
  double oldRoot = root;
  double d, root1, root2;
  
  int returnValue = 0;
       
  // Discriminant < 0 -> miss the cylinder
  if (disc > 0.0) {
    d = sqrt(disc);
    root1 = (b - d) / a;
    root2 = (b + d) / a;
         
    if (root2 > 0) {
      if(root1 < 0) {
        if(root2 < root) { 
          root = root2; 
          returnValue = -1; 
        }
      } 
      else {
        if(root1 < root) { 
          root = root1; 
          returnValue = 1; 
        }
      }
    }

    intersectionPoint = ray.getOrigin() + Rd * root;
    
    // Limit y-value to height of cylinder
    if((intersectionPoint[1] > top[1]) || (intersectionPoint[1] < bottom[1])) {
      intersectionPoint = ray.getOrigin() + Rd * root2;
      
      if((intersectionPoint[1] > top[1]) || (intersectionPoint[1] < bottom[1])) {
        root = oldRoot; 
        returnValue = 0;
      }
    }

    Ro = ray.getOrigin();

    if (Rd[1] != 0.) {
      root1 = -(Ro[1] - top[1]) / Rd[1];
      if(root1 > 0.) {
        intersectionPoint = ray.getOrigin() + Rd * root1 - center;

        if(intersectionPoint[0] * intersectionPoint[0] + intersectionPoint[2] * intersectionPoint[2] <= radiusSquare) {
          if(root1 < oldRoot) {
            root = root1; 
            returnValue = 2; 
          }
        }
      }

      root2 = -(Ro[1] - bottom[1]) / Rd[1];

      if(root2 > 0.) {
        intersectionPoint = ray.getOrigin() + Rd * root2 - center;

        if(intersectionPoint[0]*intersectionPoint[0] + intersectionPoint[2]*intersectionPoint[2] <= radiusSquare) {
          if((root2 < root1) && (root2 <oldRoot)) {
            root = root2; 
            returnValue = 2; 
          }
        }
      }
    }
  }
  return returnValue;
}

Cvec3f Cylinder::getNormal(Cvec3f &intersectionPoint) {
  if(intersectionPoint[1] == top[1]) { 
    return Cvec3f(0., 1., 0.); 
  }

  if(intersectionPoint[1] == bottom[1]) { 
    return Cvec3f(0., -1., 0.); 
  }

  Cvec3f normal = (intersectionPoint - center) / radius;
  normal[1] = 0.0;
  normal.normalize();

  return normal;
}
