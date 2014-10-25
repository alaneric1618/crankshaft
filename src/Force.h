#ifndef POINT3D_H
#define POINT3D_H
#include "Point3D.h"
#endif

#ifndef VECTOR_H
#define VECTOR_H
#include "Vector.h"
#endif

class Force {

public:
  Vector* vector;
  Point3D* point;
  Force (double x, double y, double z, double dirX, double dirY, double dirZ);
  Vector* getRotationVector();
  Vector* getTranslationVector();
};


