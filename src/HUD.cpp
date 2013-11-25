#include "HUD.h"

void HUD::drawPaused() {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 720, 480, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

  char string[80];
  std::string dummy;
  std::string stringLine;
  std::stringstream ss;

  ss << "PAUSED"; 
  stringLine = ss.str();  ss.str("");
  strcpy(string, stringLine.c_str());
  
	glColor3f(1.0, 0.0, 0.0);

	glRasterPos2f(340.0, 200.0);
	int characters = (int) strlen(string);
	for (int character = 0; character < characters; character++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[character]);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}


void HUD::drawHUD() {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 720, 480, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2f(0.0, 450.0);
	glVertex2f(720.0, 450.0);
	glVertex2f(720.0, 480.0);
	glVertex2f(0.0, 480.0);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}
