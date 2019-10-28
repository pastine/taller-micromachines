//
// Created by casimiro on 26/10/19.
//

#ifndef TALLER_MICROMACHINES_WORLDENTITIES_H
#define TALLER_MICROMACHINES_WORLDENTITIES_H


#include <tuple>
#include <vector>
#include "Car.h"
#include "Boulder.h"
#include "Oil.h"
#include "Mud.h"
#include "Camara.h"



class WorldEntities {
private:
    Car car;
    Boulder boulder;
    Oil oil;
    Mud mud;
    std::vector<std::tuple<int, int>> mud_positions;
    std::vector<std::tuple<int, int>> oil_positions;
    std::vector<std::tuple<int, int>> boulder_positions;
    std::vector<std::tuple<int, int, int>> car_positions;

public:
    enum class Entity {CAR, MUD, OIL, BOULDER};
    void put(Entity , int x, int y, int angle = 0);
    void clean();
    void render(Camara& camara);
};


#endif //TALLER_MICROMACHINES_WORLDENTITIES_H
