#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H
#include "Box2D/Box2D.h"

class Track {
private:
  b2Body* track;
public:
  explicit Track(b2World& world);
};


#endif //TALLER_MICROMACHINES_TRACK_H
