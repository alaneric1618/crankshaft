#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <OpenGl/gl.h>



#ifndef GROUP_H
#define GROUP_H
#include "Group.h"
#endif

#ifndef UPDATABLE_H
#define UPDATABLE_H
#include "Updatable.h"
#endif

#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Drawable.h"
#endif

#ifndef POINT_H
#define POINT_H
#include "Point.h"
#endif

#ifndef VECTOR_H
#define VECTOR_H
#include "Vector.h"
#endif

#ifndef FACE_H
#define FACE_H
#include "Face.h"
#endif



class Mesh : public Group, public Updatable, public Drawable {
 private:
	std::vector<Point> vertices;
	std::vector<Vector> normals;
	std::vector<Face> faces;
	
 public:
	Mesh(char* fileName);
	virtual void draw();
	virtual void update();
	

};
