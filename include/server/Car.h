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
    float min_turn_speed;
		bool visibility;
		bool crash;
    bool crash_car;
    bool powerup;
    bool slip;

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

		void contact_limit();

		bool get_crash_state();

    bool get_crash_car_state();

    bool get_powerup_state();

    bool get_slip_state();

		void back_to_track();

		~Car() override;
};


#endif //TALLER_MICROMACHINES_CAR_H
