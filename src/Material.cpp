#include "Material.h"

Material::Material() {
	ambient[0] = 0;
	ambient[1] = 0;
	ambient[2] = 0;
	
	diffuse[0] = 0;
	diffuse[1] = 0;
	diffuse[2] = 0;
	
	specular[0] = 0.0;
	specular[1] = 0.0;
	specular[2] = 0.0;
		
	shininess = 0.0;

}


Material::Material(std::string fileName) {

	//Reset colors to red to test for file read.
	ambient[0] = 0;
	ambient[1] = 0;
	ambient[2] = 0;	
	diffuse[0] = 1.0;
	diffuse[1] = 0;
	diffuse[2] = 0;
	specular[0] = 0.0;
	specular[1] = 0.0;
	specular[2] = 0.0;
	shininess = 0.0;
	diffuseTexture = 0;
	specularTexture = 0;
	
	std::string line;
  std::ifstream infile;
  infile.open("media/"+fileName);
  while (std::getline(infile, line)) {
    std::stringstream ss(line);
    std::string word;
    ss >> word;
    if (word == "Kd") {

      GLfloat r, g, b;
      ss >> r >> g >> b;
			diffuse[0] = r;
			diffuse[1] = g;
			diffuse[2] = b;

    } else if (word == "Ka") {

      GLfloat r, g, b;
      ss >> r >> g >> b;
			ambient[0] = r;
			ambient[1] = g;
			ambient[2] = b;

    } else if (word == "Ks") {

      GLfloat r, g, b;
      ss >> r >> g >> b;
			specular[0] = r;
			specular[1] = g;
			specular[2] = b;

		} else if (word == "Ni") {

      GLfloat value;
      ss >> value;
			shininess = value;

		} else if (word == "map_Kd") {

			std::string fileName;
      ss >> fileName;
			fileName = "media/"+fileName;
			diffuseTexture = createTexture(fileName.c_str());			

		} else if (word == "map_Ks") {
			
			std::string fileName;
      ss >> fileName;
			fileName = "media/"+fileName;
			specularTexture = createTexture(fileName.c_str());			

		} 

	}

}


GLuint Material::createTexture(const char *fileName)
{
	
	//Method Adapted From
	// http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
	 
	// texture data
	int width = 1024;
	int height = 1024;

	GLuint texture;
	unsigned char *data;
	FILE *file;

	// open texture data
	file = fopen(fileName, "rb");
	if (file == NULL) return 0;

	// allocate buffer
	data = (unsigned char*) malloc(width * height * 3);
 
	// read texture data
	fread(data, width * height * 3, 1, file);
	fclose(file);
 
	// allocate a texture name
	glGenTextures(1, &texture);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, texture);
 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
 
	   // when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	   // when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
 
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


	// free buffer
	free(data);
 
	return texture;
}

