#include "Car.h"
#include <cmath>

Car::Car() {
	this->add(body);
	this->add(frontLeftWheel);
	this->add(frontRightWheel);
	this->add(backLeftWheel);
	this->add(backRightWheel);
	frontLeftWheel->frame->x = -18;
	frontRightWheel->frame->x = 18;
	backLeftWheel->frame->x = -18;
	backRightWheel->frame->x = 18;
	frontLeftWheel->frame->y = 2.5;
	frontRightWheel->frame->y = 2.5;
	backLeftWheel->frame->y = 4;
	backRightWheel->frame->y = 4;
	frontLeftWheel->frame->z =  33.5;
	frontRightWheel->frame->z = 33.5;
	backLeftWheel->frame->z = -28.5;
	backRightWheel->frame->z = -28.5;
}

void Car::steer(double angle) {
	if (abs(turnAmount) < 40) {
		turnAmount += angle;
	} else {
		
	}
}

void Car::gas(double pedal) {
	
}

void Car::brake(double pedal) {
	
}

void Car::update() {
	turnAmount /= 1.2;
	double dist = turnAmount - frontLeftWheel->frame->rotationY;
	frontLeftWheel->frame->rotationY += dist/16;
	frontRightWheel->frame->rotationY+= dist/16;
	if (frame->y > 0) {
		Force* force = new Force(0.0, 0.0, 0.0, 0.0, -0.1, 0.0);
		Vector* translation = force->getTranslationVector();
		acceleration->y += translation->y;
		frame->y += acceleration->y;
	} else {
		frame->y = 0;
		acceleration->y = 0;
	}
	

	for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->update();
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
  GLfloat step = 0.1;

  for (GLfloat x = -1.0; x <= 1.0; x += step) {
    for (GLfloat z = -1.0; z < 1.0; z += step) {
      GLfloat v1[3] = {x,      1.0, z,    };
      GLfloat v2[3] = {x+step, 1.0, z,    };
      GLfloat v3[3] = {x,      1.0, z+step};
      GLfloat v4[3] = {x+step, 1.0, z+step};
      glVertex3fv(&v1[0]);
      glVertex3fv(&v4[0]);
      glVertex3fv(&v2[0]);
      
      glVertex3fv(&v1[0]);
      glVertex3fv(&v3[0]);
      glVertex3fv(&v4[0]);
    }
  }
  
  glEnd();

  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }

  glPopMatrix();
}
