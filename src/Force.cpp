#include <cmath>
#include <iostream>
#include "Force.h"


Force::Force(double x, double y, double z, double dirX, double dirY, double dirZ) {
	point = new Point3D(x, y, z);
	vector = new Vector(dirX, dirY, dirZ);
}

Vector* Force::getRotationVector() {

	//radius
	double rYZ = sqrt(pow(point->y,2)+pow(point->z,2));
	double rXZ = sqrt(pow(point->x,2)+pow(point->z,2));
	double rXY = sqrt(pow(point->x,2)+pow(point->y,2));

	//force length
	double fYZ = sqrt(pow(vector->y,2)+pow(vector->z,2));
	double fXZ = sqrt(pow(vector->x,2)+pow(vector->z,2));
	double fXY = sqrt(pow(vector->x,2)+pow(vector->y,2));

	//angle in plane
  double tYZ = acos( ( (point->y*vector->y + point->z*vector->z)/(fYZ*rYZ) ) );
  double tXZ = acos( ( (point->x*vector->x + point->z*vector->z)/(fXZ*rXZ) ) );
  double tXY = acos( ( (point->x*vector->x + point->y*vector->y)/(fXY*rXY) ) );

	if (tYZ != tYZ) tYZ = 0.0;
	if (tXZ != tXZ) tXZ = 0.0;
	if (tXY != tXY) tXY = 0.0;

	double x = (fYZ*rYZ*sin(tYZ));
	double y = (fXZ*rXZ*sin(tXZ));
	double z = (fXY*rXY*sin(tXY));

	return new Vector(x, y, z);
	
}


Vector* Force::getTranslationVector() {

	//radius
	double rYZ = sqrt(pow(point->y,2)+pow(point->z,2));
	double rXZ = sqrt(pow(point->x,2)+pow(point->z,2));
	double rXY = sqrt(pow(point->x,2)+pow(point->y,2));

	//force length
	double fYZ = sqrt(pow(vector->y,2)+pow(vector->z,2));
	double fXZ = sqrt(pow(vector->x,2)+pow(vector->z,2));
	double fXY = sqrt(pow(vector->x,2)+pow(vector->y,2));

	//angle in plane
  double tYZ = acos( ( (point->y*vector->y + point->z*vector->z)/(fYZ*rYZ) ) );
  double tXZ = acos( ( (point->x*vector->x + point->z*vector->z)/(fXZ*rXZ) ) );
  double tXY = acos( ( (point->x*vector->x + point->y*vector->y)/(fXY*rXY) ) );

	if (tYZ != tYZ) tYZ = 0.0;
	if (tXZ != tXZ) tXZ = 0.0;
	if (tXY != tXY) tXY = 0.0;

	double x = (vector->x*(cos(tXY)+cos(tXZ)) );
	double y = (vector->y*(cos(tXY)+cos(tYZ)) );
	double z = (vector->z*(cos(tXZ)+cos(tYZ)) );

	return new Vector(x, y, z);
}
