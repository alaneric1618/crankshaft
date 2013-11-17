#ifndef CAMERA_H
#define CAMERA_H
#include "Camera.h"
#endif

#include <cmath>

double Camera::time = 0;

Camera::Camera() {
  Camera::frame = new Frame();
	Camera::follow = new Frame();
}

Camera::~Camera() {
	
}

void Camera::update() {
	Camera::time += 1;
	frame->x  = 150.0*cos(time*0.01);
	frame->y  = 30;
	frame->z  = 150.0*sin(time*0.01);
	follow->y = 0;
}

void Camera::draw() {
	glLoadIdentity();
  gluLookAt(
	    frame->x,   frame->y, frame->z,     //Eye
	    follow->x,   follow->y, follow->z,     //LookAt
	    0.0,   1.0,   0.0     //Up vector
	    );  
}

void Camera::setFollow(Frame* newFollow) {
	follow = newFollow;
}


