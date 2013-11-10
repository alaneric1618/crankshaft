#include "Scenegraph.h"

SceneGraph::SceneGraph() {
	Group coordinate;
	children.push_back(coordinate);
}

SceneGraph::~SceneGraph() {
	
}

void SceneGraph::update() {
	
}

void SceneGraph::draw() {
	for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
		children[i].draw();
	}
}


