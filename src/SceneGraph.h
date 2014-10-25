#include <vector>

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

#ifndef CAR_H
#define CAR_H
#include "Car.h"
#endif

class SceneGraph : public Updatable, public Drawable {
 private:
  std::vector< Group* > children;
  Car* player;
 public:
  SceneGraph();
  ~SceneGraph();
  virtual void draw();
  virtual void update();
  void add(Group* group);
  void addCar(Car* car);
  Car* getCar();
};
