#include <iostream>
#include <vector>
#include "Box2D/Box2D.h"
#include "server/track.h"
#include "server/car.h"

int simulator() {
  b2Vec2 gravity(0.0f, 0.0f); //simulado en un mundo sin gravedad
  b2World world(gravity);

  b2Vec2 velocity(0.0f, 5.0f);
  Car car(world);
  car.set_linear_velocity(velocity);

  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  std::vector<float> x;
  std::vector<float> y;
// Game loop.
  for (int32 i = 0; i < 60; ++i) {
    world.Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position = car.get_position();
    float32 angle = car.get_angle();
    if (i%5 == 0 && i!= 0) {
      velocity.x += 1.0f;
      car.set_linear_velocity(velocity);
      float32 omega = 3.50;
      car.set_angular_velocity(omega);
    }
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }
  return 0;
}

