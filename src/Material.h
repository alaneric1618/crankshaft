#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <cstdio>
#include <cstdlib>

class Material {

 public:
	GLuint diffuseTexture;
	GLuint specularTexture;
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat shininess;
	Material();
	Material(std::string fileName);
	GLuint createTexture(const char*);

};
