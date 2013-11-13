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

#ifndef GROUP_H
#define GROUP_H
#include "Group.h"
#endif
 

class Car : public Group, public Updatable, public Drawable {	

 public:
	virtual void update();
	virtual void draw();

};
