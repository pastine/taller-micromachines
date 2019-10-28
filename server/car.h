#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H
#include "Box2D/Box2D.h"

class Car {
private:
  b2Body* m_body;
  float max_speed;
  float min_speed;

public:
  Car(b2World& world);

  b2Vec2 get_position();

  float32 get_angle();

  b2Vec2 get_lateral_velocity();

  void updateFriction();

  ~Car();

  void set_linear_velocity(b2Vec2 &v);

  void set_angular_velocity(float32 omega);

  void turn(float torque);

  b2Vec2 get_forward_velocity();

  void move_forward();
};


#endif //TALLER_MICROMACHINES_CAR_H
