#ifndef GROUP_H
#define GROUP_H
#include "Group.h"
#endif

Group::Group() {
  Group::frame = new Frame();
}

Group::~Group() {

}

void Group::add(Group* group) {
    children.push_back(group);
}

void Group::update() {
  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->update();
  }
}

void Group::draw() {

  glPushMatrix();
  glScalef(frame->scaleX, frame->scaleY, frame->scaleZ);
  glTranslatef(frame->x, frame->y, frame->z);
  glRotatef(frame->rotationX, -1.0, 0.0, 0.0);
  glRotatef(frame->rotationY, 0.0, 1.0, 0.0);
  glRotatef(frame->rotationZ, 0.0, 0.0, 1.0);
  
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.9, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	glEnd();


  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }

  glPopMatrix();
}
