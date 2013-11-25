#include <vector>

#ifndef FORCE_H
#define FORCE_H
#include "Force.h"
#endif

#ifndef FRAME_H
#define FRAME_H
#include "Frame.h"
#endif

class Dynamic {
 public:
	double mass = 1;
	Frame* acceleration;
	Frame* velocity;
	std::vector<Force*> forces;

	Dynamic();
	virtual ~Dynamic();
	virtual void evalPhysics();
	virtual void collisionDetect();

};
