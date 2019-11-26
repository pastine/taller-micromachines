#ifndef TALLER_MICROMACHINES_CARHANDLER_H
#define TALLER_MICROMACHINES_CARHANDLER_H

#include <utility>
#include <common/MoveType.h>
#include "Car.h"
#include <string>
#include <unordered_map>
#include "common/Constants.h"
#include <tuple>

class CarHandler {
private:
    Car *car;

public:
    explicit CarHandler(Car *car);

    void move(MoveType move);

    std::tuple<float, float, float> get_position();

    std::unordered_map<std::string, int> get_lives();

    std::unordered_map<std::string, bool> get_mud_state();

    std::unordered_map<std::string, bool> get_contacts_state();

    float get_speed();

		~CarHandler();
};


#endif //TALLER_MICROMACHINES_CARHANDLER_H
