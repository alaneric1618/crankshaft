#include "HUD.h"

void HUD::drawPaused() {
	
	glPushMatrix();

  glDisable(GL_LIGHTING);
	
  char string[80];
  std::string dummy;
  std::string stringLine;
  std::stringstream ss;

  ss << "PAUSED"; 
  stringLine = ss.str();  ss.str("");
  strcpy(string, stringLine.c_str());
  
	//draw highlighted line
	
	glColor3f(1.0, 0.0, 0.0);

	//setup text position;
	glRasterPos2f(0.0, 0.0);
	int characters = (int) strlen(string);
	//Draw Line of Text
	for (int character = 0; character < characters; character++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[character]);
	}
  
  glPopMatrix();

  


}
