#include "Mesh.h"

Mesh::Mesh(char* fileName) {
	
}

void Mesh::update() {
  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->update();
  }
}

void Mesh::draw() {
  glPushMatrix();
  glScalef(frame->scaleX, frame->scaleY, frame->scaleZ);
  glTranslatef(frame->x, frame->y, frame->z);
  glRotatef(frame->rotationX, -1.0, 0.0, 0.0);
  glRotatef(frame->rotationY, 0.0, 1.0, 0.0);
  glRotatef(frame->rotationZ, 0.0, 0.0, 1.0);
  


  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }

  glPopMatrix();
}
