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
  frontLeftWell->frame->rotationY = 180;
  backRightWheel->frame->rotationY = 180;
  mass = 40.0;
}

void Car::steer(double angle) {
  double velocityMagnitude = sqrt(pow(velocity->z,2)+pow(velocity->x,2));
  double sign = 0;
  turnAmount = 16*angle;
  swayAmount = angle*velocityMagnitude/25;
  double k = 0.22;
  double multiplier = (RPM)/(30*k*pow(2.17,RPM*k)); //Modeled after chi squared
  forces.push_back(new Force(0.0, 0.0, 10.0,
                             (turnAmount*multiplier),  0.0, 0.0));
  forces.push_back(new Force(0.0, 0.0,  0.0,
                             -(turnAmount*multiplier), 0.0, 0.0));
}

void Car::gas() {
  RPM += 0.18;
  bobAmount = 5.0;
}

void Car::brake() {
  double pedal = 0.3;
  RPM -= pedal;
  velocity->rotationX /= 1.01;
  velocity->rotationY /= 1.01;
  velocity->rotationZ /= 1.01;
  bobAmount = -1.0;
  brakeLight = 2000;
}

void Car::update() {
  //tires
  turnAmount /= 4;
  double dist = turnAmount - frontLeftWell->frame->rotationY;
  frontLeftWell->frame->rotationY += dist/16;
  frontRightWell->frame->rotationY+= dist/16;
  frontLeftWheel->frame->rotationX  -= RPM*3.2;
  frontRightWheel->frame->rotationX += RPM*3.2;
  backLeftWheel->frame->rotationX   -= RPM*3.3;
  backRightWheel->frame->rotationX  -= RPM*3.3;
  swayAmount /= 1.12;
  dist = swayAmount - body->frame->rotationZ;
  body->frame->rotationZ += dist/16;
  //Engin
  RPM -= 0.003;
  bobAmount /= 1.12;
  if (RPM < 0) RPM = 0;
  if (RPM > 14) RPM = 14;
  dist = bobAmount - body->frame->rotationX;
  body->frame->rotationX += dist/16;
  if (brakeLight > 75) {
    brakeLight /= 2;
  } else {
    brakeLight = 75;
  }
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
    velocity->x = sin(frame->rotationY/57.29579)*RPM;
    velocity->z = cos(frame->rotationY/57.29579)*RPM;
  }
}

void Car::draw() {
  glPushMatrix();
  glScalef(frame->scaleX, frame->scaleY, frame->scaleZ);
  glTranslatef(frame->x, frame->y, frame->z);
  glRotatef(frame->rotationX, -1.0, 0.0, 0.0);
  glRotatef(frame->rotationY, 0.0, 1.0, 0.0);
  glRotatef(frame->rotationZ, 0.0, 0.0, 1.0);

  glEnable(GL_LIGHT2);
  GLfloat position2[4] = {-12.0, 15, -20.0, 1.0};
  GLfloat diffuse2[3] =  {brakeLight, 0.5, 0.5};
  GLfloat specular2[3] = {0.1, 0.0, 0.0};
  GLfloat ambient2[3] =  {0.0, 0.0, 0.0};
  glLightfv(GL_LIGHT2, GL_POSITION, &position2[0]);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  &diffuse2[0]);
  glLightfv(GL_LIGHT2, GL_SPECULAR,  &specular2[0]);
  glLightfv(GL_LIGHT2, GL_AMBIENT,  &ambient2[0]);
  glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1);
  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 1);

  glEnable(GL_LIGHT3);
  GLfloat position3[4] = {12.0, 15, -20.0, 1.0};
  GLfloat diffuse3[3] =  {brakeLight, 0.5, 0.5};
  GLfloat specular3[3] = {0.1, 0.0, 0.0};
  GLfloat ambient3[3] =  {0.0, 0.0, 0.0};
  glLightfv(GL_LIGHT3, GL_POSITION, &position3[0]);
  glLightfv(GL_LIGHT3, GL_DIFFUSE,  &diffuse3[0]);
  glLightfv(GL_LIGHT3, GL_SPECULAR,  &specular3[0]);
  glLightfv(GL_LIGHT3, GL_AMBIENT,  &ambient3[0]);
  glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1);
  glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1);
  glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1);
  //glEnable(GL_LIGHT4);
  GLfloat position4[4] = {0.0, 20, 1500.0, 1.0};
  GLfloat direction[4] = {0.0, 0, 0.0};
  GLfloat diffuse4[3] =  {200, 200, 50};
  GLfloat specular4[3] = {0.0, 0.0, 0.0};
  GLfloat ambient4[3] =  {0.0, 0.0, 0.0};
  glLightfv(GL_LIGHT4, GL_POSITION, &position4[0]);
  glLightfv(GL_LIGHT4, GL_DIFFUSE,  &diffuse4[0]);
  glLightfv(GL_LIGHT4, GL_SPECULAR,  &specular4[0]);
  glLightfv(GL_LIGHT4, GL_AMBIENT,  &ambient4[0]);
  glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 3);
  glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0);
  glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0);
  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }
  glPopMatrix();
}
