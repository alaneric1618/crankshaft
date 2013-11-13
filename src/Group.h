#include <vector>

#include <OpenGl/gl.h>

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



class Group : public Updatable, public Drawable {	

protected:
  Frame* frame;
  std::vector< Group* > children;
public:
  Group();
  virtual ~Group();
  virtual void update();
  virtual void draw();
  virtual void add(Group* group);
};
