#include "Scenegraph.h"
#include <iostream>


SceneGraph::SceneGraph() {
	
}

SceneGraph::~SceneGraph() {
  
}

void SceneGraph::update() {
  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->update();
  }
}

void SceneGraph::draw() {
  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }
}

void SceneGraph::add(Group* group) {
    children.push_back(group);
}



