//
// Created by casimiro on 26/10/19.
//

#ifndef TALLER_MICROMACHINES_WORLDENTITIES_H
#define TALLER_MICROMACHINES_WORLDENTITIES_H


#include <tuple>
#include <vector>
#include <common/json.h>
#include "Car.h"
#include "Boulder.h"
#include "Oil.h"
#include "Mud.h"
#include "Camera.h"
#include "StraightRoad.h"
#include "CurvedRoad.h"


class WorldEntities {
private:
    Car car;
    Boulder boulder;
    Oil oil;
    Mud mud;
    StraightRoad straight_road;
    CurvedRoad curved_road;
    std::vector<std::tuple<int, int>> mud_positions;
    std::vector<std::tuple<int, int>> oil_positions;
    std::vector<std::tuple<int, int>> boulder_positions;
    std::vector<std::tuple<int, int, int, int>> car_positions;
    std::vector<std::tuple<int, int, int>> straight_road_positions;
    std::vector<std::tuple<int, int, int>> curved_road_positions;

public:
    enum class Entity {CAR, MUD, OIL, BOULDER, STRAIGHT_ROAD, CURVED_ROAD};
    void put(Entity , int x, int y, int angle = 0, int id = 0);
    void clean();
    void render(Camera& camera);
};


#endif //TALLER_MICROMACHINES_WORLDENTITIES_H
