//c++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

//c libraries
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdlib>

#include "Game.h"

SceneGraph* Game::sceneGraph = new SceneGraph();

void Game::keyboard (unsigned char key, int x, int y) {
  switch (key) {
    //Camera Movement
  
  default: break;
  }
  glutPostRedisplay();
}

//This method handles all user interaction with the HUD
void Game::keyboardSpecial (int key, int x, int y) {
	switch (key) {
		//Camera Movement
	case GLUT_KEY_UP: 

		break;

	case GLUT_KEY_DOWN: 

		break;

	case GLUT_KEY_LEFT:

		break;
      
	case GLUT_KEY_RIGHT:

		break;
      

	default: break;
	}
}

// Should only be used for physics simulation
void Game::update() {
	Game::sceneGraph->update();
  draw();
}


// Primary draw loop from which all other drawing happens.
void Game::draw(void) {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glPushMatrix();
  //glScalef(zoom, zoom, zoom);
  //glTranslatef(translation[0], translation[1], translation[2]);
  //glRotatef(rotation[0], 0.0, 1.0, 0.0);
  //glRotatef(rotation[1], -1.0, 0.0, 0.0);
  //glRotatef(rotation[2], 0.0, 0.0, 1.0);

	Game::sceneGraph->draw();

  glFlush();
  glutSwapBuffers();
}

void Game::reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (width <= height) {
    glOrtho(-2.0, 2.0, -2.0*(GLfloat)height/(GLfloat)width, 2.0*(GLfloat)height/(GLfloat)width,-600, 600);
  } else { 
    glOrtho(-2.0*(GLfloat)width/(GLfloat)height, 2.0*(GLfloat)width/(GLfloat)height, -2.0,2.0, -600, 600); 
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Game::initGlut(int argc, char** argv) {
  std::cout << "Game Initiated \n";
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(1280,720);
  glutCreateWindow(argv[0]);
  Game::initGL();
  glutDisplayFunc(Game::draw);
  glutReshapeFunc(Game::reshape);
  glutKeyboardFunc(Game::keyboard);
  glutSpecialFunc(Game::keyboardSpecial);
  glutIdleFunc(Game::update);
  glutMainLoop();
}

void Game::initGL() {
  glEnable(GL_DEPTH_TEST);  
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 
  glPointSize(3.0);
}


// TODO: readFile needs to be expanded to read all
// data in a file. Normals should be added soon.
void Game::readFile(int argc, char** argv) {
  std::string line;
  std::ifstream infile;
  infile.open(argv[argc-1]);
  while (std::getline(infile, line)) {
    std::stringstream ss(line);
    std::string word;
    ss >> word;
    if (word == "v") {
      double x, y, z;
      ss >> x >> y >> z;
      //vertices.push_back( Point(x,y,z) );
    } else if (word == "f") {
      int one, two, three;
      ss >> one >> two >> three;
      //faces.push_back( Index(one-1, two-1, three-1) );
    }
  }
}

int main(int argc, char** argv)
{
  Game::initGlut(argc, argv);
  return 0;
}




