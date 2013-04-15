#ifndef RAY_H
#define RAY_H

#include "cvec.h"

class Ray {

public:
	// Constructors
  Ray();
  Ray(const Cvec3f &origin_, Cvec3f &direction_);
  // Accessors
  Cvec3f setOrigin(Cvec3f &origin_) { 
    origin = origin_; 
  }
  Cvec3f setDirection(Cvec3f &direction_) { 
    direction = direction_;
  }
  Cvec3f &getOrigin() { 
    return origin;
  }
  Cvec3f &getDirection() { 
    return direction; 
  }

private:
  Cvec3f origin;
  Cvec3f direction;
};

#endif