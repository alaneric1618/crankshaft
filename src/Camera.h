#ifndef UPDATABLE_H
#define UPDATABLE_H
#include "Updatable.h"
#endif

#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Drawable.h"
#endif

#ifndef FRAME_H
#define FRAME_H
#include "Frame.h"
#endif

#ifndef GLU_H
#define GLU_H
#include <OpenGL/glu.h>
#endif

class Camera : public Updatable, public Drawable {

protected:
  Frame* frame;
	Frame* follow;
public:
	static double time;
  Camera();
  virtual ~Camera();
  virtual void update();
  virtual void draw();
	void setFollow(Frame* newFollow);
};

