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

class Group : public Updatable, public Drawable {	

 private:
	std::vector< Group > children;
 public:
	Group();
	~Group();
	virtual void update();
	virtual void draw();

};
