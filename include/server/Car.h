#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "common/Constants.h"
#include <string>

class Car : public Entity {
private:
    float max_speed;
    float min_speed;
    bool track;
    int *lives;
    bool visibility;

public:
    explicit Car(b2World &world, unsigned long i);

    b2Vec2 get_position() override;

    float32 get_angle();

    void move_straight(bool move_forward);

    void start_contact(int id);

    void end_contact(int id);

    void turn(bool turn_left);

    void on_track();

    void off_track();

    void surface_effect();

    int get_entity_type() override;

    void contact_mud();

    void contact_oil();

    void contact_stone();

    void contact_health();

    void contact_boost();

    void contact_car();

    int get_lives();

    bool get_mud_state();

    float get_speed();

    bool isMoving();

    void contact_limit();

    int min_turn_speed;

		~Car() override;
};


#endif //TALLER_MICROMACHINES_CAR_H
