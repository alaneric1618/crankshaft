#include <vector>
#include <OpenGl/gl.h>

#ifndef DYNAMIC_H
#define DYNAMIC_H
#include "Dynamic.h"
#endif

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

#ifndef FORCE_H
#define FORCE_H
#include "Force.h"
#endif
 
#ifndef MESH_H
#define MESH_H
#include "Mesh.h"
#endif

class Car : public Group, public Dynamic, public Updatable, public Drawable {	
 public:
	Mesh* body            = new Mesh("media/Car.obj");
	Group* frontLeftWell  = new Group();
	Group* frontRightWell  = new Group();
	Mesh* frontLeftWheel  = new Mesh("media/Wheel.obj");
	Mesh* frontRightWheel = new Mesh("media/Wheel.obj");
	Mesh* backLeftWheel   = new Mesh("media/Wheel.obj");
	Mesh* backRightWheel  = new Mesh("media/Wheel.obj");
	double turnAmount = 0.0;
	double bobAmount = 0.0;
	double swayAmount = 0.0;
	double RPM = 0;
	double brakeLight = 75;

	Car();
	void steer(double angle);
	void gas();
	void brake();
	virtual void update();
	virtual void draw();
	virtual void evalPhysics();
	virtual void collisionDetect();
};
