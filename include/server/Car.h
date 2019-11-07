#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H
#include "Box2D/Box2D.h"
#include "ContactListener.h"

class Car {
private:
  b2Body* car;
  float max_speed;
  float min_speed;
  int contacts;
  ContactListener listener;
  bool track;

public:
  explicit Car(b2World &world, unsigned long i);

  b2Vec2 get_position();

  float32 get_angle();

  b2Vec2 get_lateral_velocity();

  void updateFriction();

  void set_linear_velocity(b2Vec2 &v);

  void set_angular_velocity(float32 omega);

  void turn(float torque);

  b2Vec2 get_forward_velocity();

  void move_forward();

  void stop();

  void start_contact();

  void end_contact();

  ~Car();

  bool is_colliding();

  void turn_right();

  void on_track();

  void off_track();
};


#endif //TALLER_MICROMACHINES_CAR_H
