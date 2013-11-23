#include <string>
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

#ifndef POINT2D_H
#define POINT2D_H
#include "Point2D.h"
#endif

#ifndef POINT3D_H
#define POINT3D_H
#include "Point3D.h"
#endif

#ifndef VECTOR_H
#define VECTOR_H
#include "Vector.h"
#endif

#ifndef FACE_H
#define FACE_H
#include "Face.h"
#endif

#ifndef MATERIAL_H
#define MATERIAL_H
#include "Material.h"
#endif

class Mesh : public Group, public Updatable, public Drawable {
 private:
	std::vector<Point3D> vertices;
	std::vector<Point2D> textures;
	std::vector<Vector> normals;
	std::vector<Face> faces;
	Material material;

 public:
	Mesh(std::string fileName);
	Mesh(std::string fileName, double offsetX, double offsetY, double scaleX, double scaleY);
	virtual void draw();
	virtual void update();

};
