#include <vector>
#include <OpenGl/gl.h>

#ifndef UPDATABLE_H
#define UPDATABLE_H
#include "Updatable.h"
#endif

#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Drawable.h"
#endif

#ifndef GROUP_H
#define GROUP_H
#include "Group.h"
#endif
 
#ifndef MESH_H
#define MESH_H
#include "Mesh.h"
#endif
 
class Car : public Group, public Updatable, public Drawable {	
 public:
	Mesh* body            = new Mesh("media/Car.obj");
	Mesh* frontLeftWheel  = new Mesh("media/Wheel.obj");
	Mesh* frontRightWheel = new Mesh("media/Wheel.obj");
	Mesh* backLeftWheel   = new Mesh("media/Wheel.obj");
	Mesh* backRightWheel  = new Mesh("media/Wheel.obj");

	Car();
	virtual void update();
	virtual void draw();

};
