#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H
#include "Box2D.h"

class Track {
private:
  b2World world;
public:
  Track(b2Vec2 gravity);

  void step(float32 timeStep, int32 velocityIt, int32 positionIt);
};


#endif //TALLER_MICROMACHINES_TRACK_H
