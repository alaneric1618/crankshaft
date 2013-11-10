#include "Group.h"

Group::Group() {

}

Group::~Group() {

}

void Group::update() {
	
}

void Group::draw() {
	glDisable(GL_LIGHTING);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.9, 0.9, 0.9);
  glBegin(GL_TRIANGLES);
  GLfloat step = 0.1;
  for (GLfloat x = -1.0; x <= 1.0; x += step) {
    for (GLfloat z = -1.0; z < 1.0; z += step) {
      GLfloat v1[3] = {x,      0.0, z,    };
      GLfloat v2[3] = {x+step, 0.0, z,    };
      GLfloat v3[3] = {x,      0.0, z+step};
      GLfloat v4[3] = {x+step, 0.0, z+step};
      glVertex3fv(&v1[0]);
      glVertex3fv(&v4[0]);
      glVertex3fv(&v2[0]);
      glVertex3fv(&v1[0]);
      glVertex3fv(&v3[0]);
      glVertex3fv(&v4[0]);
    }
  }
  
  glEnd();
}
