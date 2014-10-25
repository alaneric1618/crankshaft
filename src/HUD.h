//c libraries
#include <OpenGL/gl.h>

#ifndef GLU_H
#define GLU_H
#include <OpenGL/glu.h>
#endif

#ifndef FRAME_H
#define FRAME_H
#include "Frame.h"
#endif

#include <GLUT/glut.h>

#include <sstream>
#include <string>

class HUD {
public:
  void drawPaused();
  void drawHUD();
};
