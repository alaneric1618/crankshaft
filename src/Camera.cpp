#ifndef CAMERA_H
#define CAMERA_H
#include "Camera.h"
#endif

#include <cmath>

Camera::Camera() {
  time = 0;
  Camera::follow = new Frame();
  Camera::follow = new Frame();
}

Camera::~Camera() {

}

void Camera::update() {
  time = -1.4;
  double distX =
    look->x
    + 150.0*cos(-(look->rotationY/57.2957)-3.1415/2)
    - follow->x;
  double distZ =
    look->z
    + 150.0*sin(-(look->rotationY/57.2957)-3.1415/2)
    - follow->z;
  follow->x  += distX/32;
  follow->y  = 60;
  follow->z  += distZ/32;
}

void Camera::pause() {
  time += 0.005;
  follow->x += (look->x + 150.0*cos(time) - follow->x)/64;
  follow->y = 0;
  follow->z += (look->z + 150.0*sin(time) - follow->z)/64;
}

void Camera::draw() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
            follow->x,   follow->y, follow->z,     //Eye
            look->x,   look->y+40, look->z,     //LookAt
            0.0,   1.0,   0.0     //Up vector
            );
}

void Camera::setFollow(Frame* newFollow) {
  follow = newFollow;
}

void Camera::setLook(Frame* newLook) {
  look = newLook;
}


