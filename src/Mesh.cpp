#include "Mesh.h"

Mesh::Mesh(char* fileName) {

	std::string line;
  std::ifstream infile;
  infile.open(fileName);
  while (std::getline(infile, line)) {
    std::stringstream ss(line);
    std::string word;
    ss >> word;
    if (word == "v") {

      double x, y, z;
      ss >> x >> y >> z;
      vertices.push_back( Point(x,y,z) );

    } else if (word == "f") {
			
			int index[3];
			int texture[3];
			int normal[3];

			std::string token;
			std::cout << std::endl;
			std::cout << "f";

			for (int i = 0; i < 3; i++) {
				std::getline(ss, token, '/');
				std::cout << token << " ";
				index[i] = atoi(token.c_str());
				token = "";
				std::getline(ss, token, ' ');
				std::cout << token << " ";
				texture[i] = atoi(token.c_str());
				token = "";
			}

			std::cout << std::endl;
			std::cout << "f " << index[0] << "     " << index[1] << "     " << index[2] << std::endl;
      faces.push_back( Face(index[0]-1, index[1]-1, index[2]-1) );

    }
  }

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
  
  glColor3f(0,0,1);
	glBegin(GL_TRIANGLES);
	for(std::vector<Face>::iterator it = faces.begin(); it != faces.end(); ++it) {
		Face face = *it;
		glVertex3f(vertices[face.v1].x, vertices[face.v1].y, vertices[face.v1].z);
    glVertex3f(vertices[face.v2].x, vertices[face.v2].y, vertices[face.v2].z);
    glVertex3f(vertices[face.v3].x, vertices[face.v3].y, vertices[face.v3].z);
	}

  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }

  glPopMatrix();
}
