#include "Car.h"
#include <cmath>

Car::Car() {
	this->add(body);
	body->frame->rotationX = 2;
	body->frame->y = -1;
	this->add(frontLeftWell);
	this->add(frontRightWell);
	frontLeftWell->add(frontLeftWheel);
	frontRightWell->add(frontRightWheel);
	this->add(backLeftWheel);
	this->add(backRightWheel);
	frontLeftWell->frame->x = -18;
	frontRightWell->frame->x = 18;
	backLeftWheel->frame->x = -15.8;
	backRightWheel->frame->x = 15.8;
	frontLeftWell->frame->y = 2.5;
	frontRightWell->frame->y = 2.5;
	backLeftWheel->frame->y = 2.5;
	backRightWheel->frame->y = 2.5;
	frontLeftWell->frame->z =  33.5+29;
	frontRightWell->frame->z = 33.5+29;
	backLeftWheel->frame->z = -28.5+29;
	backRightWheel->frame->z = -28.5+29;
	backLeftWheel->frame->scaleX = 1.1;
	backLeftWheel->frame->scaleY = 1.1;
	backLeftWheel->frame->scaleZ = 1.1;
	backRightWheel->frame->scaleX = 1.1;
	backRightWheel->frame->scaleY = 1.1;
	backRightWheel->frame->scaleZ = 1.1;
	mass = 40.0;
}

void Car::steer(double angle) {
	double velocityMagnitude = sqrt(pow(velocity->z,2)+pow(velocity->x,2));
	forces.push_back(new Force(0.0, 0.0, 10.0, angle*4,  0.0, 0.0));
	forces.push_back(new Force(0.0, 0.0,  0.0, -angle*4, 0.0, 0.0));
	turnAmount = 16*angle;
	swayAmount = angle*velocityMagnitude/25;
	
}

void Car::gas() {
	RPM += 0.1;
	bobAmount = 3.0;
}

void Car::brake() {
	double pedal = 0.14;
	RPM -= pedal;
	velocity->rotationX /= 1.01;
	velocity->rotationY /= 1.01;
	velocity->rotationZ /= 1.01;
	bobAmount = -1.0;
}

void Car::update() {
	//tires
	turnAmount /= 4;
	double dist = turnAmount - frontLeftWell->frame->rotationY;
	frontLeftWell->frame->rotationY += dist/16;
	frontRightWell->frame->rotationY+= dist/16;
	frontLeftWheel->frame->rotationX  -= RPM*3.2;
	frontRightWheel->frame->rotationX -= RPM*3.2;
	backLeftWheel->frame->rotationX   -= RPM*3.3;
	backRightWheel->frame->rotationX  -= RPM*3.3;
	swayAmount /= 1.01;
	dist = swayAmount - body->frame->rotationZ;
	body->frame->rotationZ += dist/16;
	

	//Engin
	RPM -= 0.003;
	bobAmount /= 1.01;
	if (RPM < 0) RPM = 0;
	if (RPM > 10) RPM = 10;
	dist = bobAmount - body->frame->rotationX;
	body->frame->rotationX += dist/16;


	//general physics
	collisionDetect();
	evalPhysics();

	//update children
	for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->update();
  }
}

void Car::evalPhysics() {

	//reset acceleration
	acceleration->x = 0.0;
	acceleration->y = 0.0;
	acceleration->z = 0.0;
	acceleration->rotationX = 0.0;
	acceleration->rotationY = 0.0;
	acceleration->rotationZ = 0.0;

	//Gravity
	forces.push_back(new Force(0.0, 0.0, 0.0, 0.0, -9.8, 0.0));
		
	//add forces to acceleration
	for(std::vector<Force>::size_type i = 0; i != forces.size(); i++) {
			Force* force = forces[i];
			Vector* rotation = force->getRotationVector();
			Vector* translation = force->getTranslationVector();
			acceleration->x += translation->x/mass;
			acceleration->y += translation->y/mass;
			acceleration->z += translation->z/mass;
			acceleration->rotationX += rotation->x/mass*0.01;
			acceleration->rotationY += rotation->y/mass*0.01;
			acceleration->rotationZ += rotation->z/mass*0.01;
  }
	
	//Dampen rotational velocity
	velocity->rotationY /= 1.1;

	//add acceleration to velocity
	velocity->x += acceleration->x;
	velocity->y += acceleration->y;
	velocity->z += acceleration->z;
	velocity->rotationX += acceleration->rotationX;
	velocity->rotationY += acceleration->rotationY;
	velocity->rotationZ += acceleration->rotationZ;

	
	//add velocity to frame
	frame->x += velocity->x;
	frame->y += velocity->y;
	frame->z += velocity->z;
	frame->rotationX += velocity->rotationX;
	frame->rotationY += velocity->rotationY;
	frame->rotationZ += velocity->rotationZ;
	
	//slow velocity (friction)

	//Dump Forces
	forces.clear();
	
}

void Car::collisionDetect() {
	if (frame->y <= 0) {
		forces.push_back(new Force(0.0, 0.0, 0.0, 
															 0.0, -velocity->y*mass*1.2, 0.0));
		frame->y = 0;
	}
	if (frame->y <= 1) {
		velocity->x = sin(frame->rotationY/57)*RPM;
		velocity->z = cos(frame->rotationY/57)*RPM;		
	}
}

void Car::draw() {
	
  glPushMatrix();
  glScalef(frame->scaleX, frame->scaleY, frame->scaleZ);
  glTranslatef(frame->x, frame->y, frame->z);
  glRotatef(frame->rotationX, -1.0, 0.0, 0.0);
  glRotatef(frame->rotationY, 0.0, 1.0, 0.0);
  glRotatef(frame->rotationZ, 0.0, 0.0, 1.0);


  glDisable(GL_LIGHTING);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.9, 0.2, 0.2);
  glBegin(GL_TRIANGLES);
  
  glEnd();

  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }

  glPopMatrix();
}
