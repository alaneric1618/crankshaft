#include "Mesh.h"

Mesh::Mesh(std::string fileName) {
	std::cout << "Reading Object File: " << fileName << std::endl;

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
      vertices.push_back( Point3D(x,y,z) );

    } else if (word == "vn") {

      double x, y, z;
      ss >> x >> y >> z;
      normals.push_back( Vector(x,y,z) );

		} else if (word == "vt") {

      double x, y;
      ss >> x >> y;
      textures.push_back( Point2D(
																	(0.33 * x + 0), 
																	(-0.33 * y + 1)) 
													);

    } else if (word == "f") {
			
			int index[3];
			int texture[3];
			int normal[3];

			std::string token;

			for (int i = 0; i < 3; i++) {
				std::getline(ss, token, '/');
				index[i] = atoi(token.c_str());
				token = "";

				std::getline(ss, token, '/');
				texture[i] = atoi(token.c_str());
				token = "";

				std::getline(ss, token, ' ');
				normal[i] = atoi(token.c_str());
				token = "";
			}

      faces.push_back( 
											Face(  index[0]-1,   index[1]-1,   index[2]-1,
													 texture[0]-1, texture[1]-1, texture[2]-1,
														normal[0]-1,  normal[1]-1,  normal[2]-1)
											 );

    } else if (word == "mtllib") {

			std::string fileName;
			ss >> fileName;
			Mesh::material = Material( fileName );

		}


  }


}

Mesh::Mesh(std::string fileName, 
					 double offsetX, double offsetY,
					 double scaleX, double scaleY
					 ) {

	std::cout << "Reading Object File: " << fileName << std::endl;

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
      vertices.push_back( Point3D(x,y,z) );

    } else if (word == "vn") {

      double x, y, z;
      ss >> x >> y >> z;
      normals.push_back( Vector(x,y,z) );

		} else if (word == "vt") {

      double x, y;
      ss >> x >> y;
      textures.push_back( Point2D(
																	(scaleX * x + offsetX), 
																	(scaleY*y + offsetY)) 
													);

    } else if (word == "f") {
			
			int index[3];
			int texture[3];
			int normal[3];

			std::string token;

			for (int i = 0; i < 3; i++) {
				std::getline(ss, token, '/');
				index[i] = atoi(token.c_str());
				token = "";

				std::getline(ss, token, '/');
				texture[i] = atoi(token.c_str());
				token = "";

				std::getline(ss, token, ' ');
				normal[i] = atoi(token.c_str());
				token = "";
			}

      faces.push_back( 
											Face(  index[0]-1,   index[1]-1,   index[2]-1,
													 texture[0]-1, texture[1]-1, texture[2]-1,
														normal[0]-1,  normal[1]-1,  normal[2]-1)
											 );

    } else if (word == "mtllib") {

			std::string fileName;
			ss >> fileName;
			material = Material( fileName );

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

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
	

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture( GL_TEXTURE_2D, material.diffuseTexture );  
	//glBindTexture( GL_TEXTURE_2D, material.specularTexture );  
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

  //glColor3f(0,0,1);

  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   &Mesh::material.ambient[0]);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   &Mesh::material.diffuse[0]);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  &Mesh::material.specular[0]);
  //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,  Mesh::material.shininess);

	glBegin(GL_TRIANGLES);
	for(std::vector<Face>::iterator it = faces.begin(); it != faces.end(); ++it) {
		Face face = *it;
		glTexCoord2d(textures[face.t1].x, textures[face.t1].y);
		glNormal3f(normals[face.n1].x, normals[face.n1].y, normals[face.n1].z);
		glVertex3f(vertices[face.v1].x, vertices[face.v1].y, vertices[face.v1].z);

		glTexCoord2d(textures[face.t2].x, textures[face.t2].y);
		glNormal3f(normals[face.n2].x, normals[face.n2].y, normals[face.n2].z);
    glVertex3f(vertices[face.v2].x, vertices[face.v2].y, vertices[face.v2].z);

		glTexCoord2d(textures[face.t3].x, textures[face.t3].y);
		glNormal3f(normals[face.n3].x, normals[face.n3].y, normals[face.n3].z);
    glVertex3f(vertices[face.v3].x, vertices[face.v3].y, vertices[face.v3].z);
	}

	glEnd();

  for(std::vector<Group>::size_type i = 0; i != children.size(); i++) {
    children[i]->draw();
  }

  glPopMatrix();
}
