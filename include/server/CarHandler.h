#ifndef TALLER_MICROMACHINES_CARHANDLER_H
#define TALLER_MICROMACHINES_CARHANDLER_H

#include <utility>
#include <common/MoveType.h>
#include "Car.h"
#include <string>
#include <unordered_map>
#include "common/Constants.h"

class CarHandler {
private:
    Car *car;

public:
    explicit CarHandler(Car *car);

    void move(MoveType move);

    float get_x();

    float get_y();

    std::unordered_map<std::string, std::string> get_position();

    float32 get_angle();

    void update_surface();

    ~CarHandler();

    std::unordered_map<std::string, std::string> get_user_state();

    bool isMoving();
};


#endif //TALLER_MICROMACHINES_CARHANDLER_H
