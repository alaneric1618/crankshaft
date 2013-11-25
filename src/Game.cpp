//c++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

//c libraries
#include <OpenGL/gl.h>

#ifndef GLU_H
#define GLU_H
#include <OpenGL/glu.h>
#endif

#ifndef FORCE_H
#define FORCE_H
#include "Force.h"
#endif

#include <GLUT/glut.h>
#include <cstdlib>

#include "Game.h"

int Game::gameState = 0; //set game to loading state
HUD* Game::hud = new HUD();
Camera* Game::camera = new Camera();
SceneGraph* Game::sceneGraph = new SceneGraph();

void Game::keyboard (unsigned char key, int x, int y) {

  switch (key) {
		
	case ' ':
		if (Game::gameState == 1) {
			Game::gameState = 2;
			break;
		}
		if (Game::gameState == 2) Game::gameState = 1;
		break;

	case 'a':
		Game::sceneGraph->getCar()->steer(20.0);
		break;

	case 'd':
		Game::sceneGraph->getCar()->steer(-20.0);
		break;

	case 'w':
		Game::sceneGraph->getCar()->gas();
		break;

	case 's':
		Game::sceneGraph->getCar()->brake();
		break;

  
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


void Game::initScene() {
	//Create Objects
	Car* car = new Car();
	Mesh* floor = new Mesh("media/Floor.obj", 0.0, 0.0, 100.0, 100.0);
	Mesh* sky = new Mesh("media/Sky.obj", 0.0, 1.0, 1.0, -1.0);

	//Move Object
	car->frame->y = 280;
	floor->frame->y = 4.4;
	sky->frame->scaleX = 3;
	sky->frame->scaleY = 3;
	sky->frame->scaleZ = 3;
	floor->frame->scaleX = 4;
	floor->frame->scaleY = 4;
	floor->frame->scaleZ = 4;

	//Setup Objects
	Game::camera->setLook(car->frame);


	//Add Objects to Scene
  Game::sceneGraph->add(sky);
	Game::sceneGraph->add(floor);
	Game::sceneGraph->addCar(car);

	//set game to active state
	Game::gameState = 1;
}



// Should only be used for physics simulation
void Game::update() {
	switch (Game::gameState) {
	case 0: //loading 
		break;
	case 1: //active
		Game::camera->update(); 
		Game::sceneGraph->update();
		break;
	case 2: //paused
		Game::camera->pause();
		break;
	case 3: //error
		break;
	}
}


// Primary draw loop from which all other drawing happens.
void Game::draw(void) {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glShadeModel(GL_SMOOTH);

  GLfloat position[3] = {20, 30, 20};
	glLightfv(GL_LIGHT0, GL_POSITION, &position[0]);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	switch (Game::gameState) {
	case 0: //loading 
		break;
	case 1: //active
		Game::camera->draw();
		Game::sceneGraph->draw();
		break;
	case 2: //paused
		Game::hud->drawPaused();
		Game::camera->draw();
		Game::sceneGraph->draw();
		break;
	case 3: //error
		break;
	}



  glFlush();
  glutSwapBuffers();
	glutPostRedisplay();
}

void Game::reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gluPerspective(37.8, ((double)width/(double)height), 1, 10000);

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
  glutKeyboardFunc(Game::keyboard);
  glutSpecialFunc(Game::keyboardSpecial);
}

void Game::initLoop() {
	glutDisplayFunc(Game::draw);
  glutReshapeFunc(Game::reshape);
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

int main(int argc, char** argv)
{
  Game::initGlut(argc, argv);
	Game::initScene();
	Game::initLoop();
  return 0;
}




