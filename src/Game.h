#include "HUD.h"
#include "Camera.h"
#include "SceneGraph.h"

#ifndef MESH_H
#define MESH_H
#include "Mesh.h"
#endif

#ifndef CAR_H
#define CAR_H
#include "Car.h"
#endif

#ifndef GROUP_H
#define GROUP_H
#include "Group.h"
#endif

class Game {

 private:

 public:
	static int gameState;  //0=loading, 1=active, 2=paused, 3=error
	static HUD * hud;
	static Camera * camera;
	static SceneGraph * sceneGraph;
	static void update();
	static void draw();
	static void initScene();
	static void initGlut(int argc, char** argv);
	static void initGL();
	static void initLoop();
	static void keyboard(unsigned char key, int x, int y);
	static void keyboardSpecial(int key, int x, int y);
	static void reshape(int w, int h);
	static void readFile(int argc, char** argv);
	static void drawCoordinate();
	static void drawFile();
	static void drawInfo();

};






