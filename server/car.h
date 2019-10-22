#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H
#include "Box2D/Box2D.h"

class Car {
private:
  b2Body* m_body;

public:
  Car(b2World& world);

  b2Vec2 get_position();

  float32 get_angle();

  b2Vec2 getLateralVelocity();

  void updateFriction();

  ~Car();
};


#endif //TALLER_MICROMACHINES_CAR_H
