#include <cmath>
#include <iostream>
#include "Force.h"


Force::Force(double x, double y, double z,
             double dirX, double dirY, double dirZ) {
  point = new Point3D(x, y, z);
  vector = new Vector(dirX, dirY, dirZ);
}

Vector* Force::getRotationVector() {
  double x = point->y*vector->z - point->z*vector->y;
  double y = point->z*vector->x - point->x*vector->z;
  double z = point->x*vector->y - point->y*vector->x;
  return new Vector(x, y, z);
}


Vector* Force::getTranslationVector() {
  return new Vector(vector->x, vector->y, vector->z);
}
