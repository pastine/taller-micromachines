#include "Box2D.h"
#include "track.h"
#include "car.h"

int main() {
  b2Vec2 gravity(0.0f, 0.0f); //simulado en un mundo sin gravedad
  b2World world(gravity);

  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  Car car(world);

// Game loop.
  for (int32 i = 0; i < 60; ++i) {
    world.Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position = car.get_position();
    float32 angle = car.get_angle();

    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }

  return 0;
}

