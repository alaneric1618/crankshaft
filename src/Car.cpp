#include "Car.h"

void Car::update() {
  frame->rotationZ -= 0.2;
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

  glPopMatrix();
}
