#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H
#include "Box2D/Box2D.h"
#include "Entity.h"

class Car : public Entity {
private:
  b2Body* car;
  float max_speed;
  float min_speed;
  bool track;
  int lives;
  bool visibility;

public:
  explicit Car(b2World &world, unsigned long i);

  b2Vec2 get_position();

  float32 get_angle();

  b2Vec2 get_lateral_velocity();

  b2Vec2 get_forward_velocity();

  void move_forward();

  void stop();

  void start_contact(int ID);

  void end_contact(int ID);

  ~Car();

  void turn_right();

  void on_track();

  void off_track();

  void surface_effect();

  void turn_left();

	int get_entity_type() override;

	void contact_mud();

	void contact_oil();

	void contact_stone();

	void contact_health();

	void contact_boost();

	void contact_car();
};


#endif //TALLER_MICROMACHINES_CAR_H
