#include "track.h"
#include "Box2D/Box2D.h"

Track::Track(b2Vec2 gravity) : world(b2World(gravity)) {
}

void Track::step(float32 timeStep, int32 velocityIt, int32 positionIt) {
  world.Step(timeStep, velocityIt, positionIt);
}