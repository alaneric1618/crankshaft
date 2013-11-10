#include <vector>

#ifndef UPDATABLE_H
#define UPDATABLE_H
#include "Updatable.h"
#endif

#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Drawable.h"
#endif

#include "Group.h"

class SceneGraph : public Updatable, public Drawable {
 private:
	std::vector< Group > children;
 public:
	SceneGraph();
	~SceneGraph();
	virtual void draw();
	virtual void update();

};
