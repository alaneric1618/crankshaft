#include "SceneGraph.h"

class Game {

 private:

 public:
	static SceneGraph * sceneGraph;
	static void update();
	static void draw();
	static void initCamera();
	static void initGlut(int argc, char** argv);
	static void initGL();
	static void keyboard(unsigned char key, int x, int y);
	static void keyboardSpecial(int key, int x, int y);
	static void reshape(int w, int h);
	static void readFile(int argc, char** argv);
	static void drawCoordinate();
	static void drawFile();
	static void drawInfo();

};






