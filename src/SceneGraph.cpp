#include "Scenegraph.h"
#include <iostream>


SceneGraph::SceneGraph() {
  Group* coordinate = new Group;
  Car* car = new Car;
  coordinate->add(car);
  children.push_back( coordinate );
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


