#ifndef TALLER_MICROMACHINES_WORLDENTITIES_H
#define TALLER_MICROMACHINES_WORLDENTITIES_H


#include <tuple>
#include <vector>
#include <common/json.h>
#include <queue>
#include "Car.h"
#include "Boulder.h"
#include "Oil.h"
#include "Mud.h"
#include "Camera.h"
#include "StraightRoad.h"
#include "CurvedRoad.h"
#include "Boost.h"
#include "Heart.h"
#include "MudSplatter.h"
#include "Explotion.h"


class WorldEntities {
private:
    Car car;
    Boulder boulder;
    Oil oil;
    Mud mud;
    StraightRoad straight_road;
    CurvedRoad curved_road;
    Boost boost;
    Heart heart;

    std::vector<std::tuple<float, float>> mud_positions;
    std::vector<std::tuple<float, float>> oil_positions;
    std::vector<std::tuple<float, float>> boulder_positions;
    std::vector<std::tuple<float, float, float, float, float>> car_positions;
    std::vector<std::tuple<float, float, float>> straight_road_positions;
    std::vector<std::tuple<float, float, float>> curved_road_positions;
    std::vector<std::tuple<float, float>> boost_positions;
    std::vector<std::tuple<float, float>> heart_positions;

    std::queue<std::tuple<Explotion, float, float>> explotion_positions;

    void _render_simple_object(std::vector<std::tuple<float, float>> &positions,
                               Renderizable &object,
                               Camera &camera);

public:
    enum class Entity {
        CAR, MUD, OIL, BOULDER, STRAIGHT_ROAD, CURVED_ROAD, BOOST, HEART
    };

    void put(Entity, float x, float y, float angle = 0, int id = 0, float speed = 0);

    void put_explotion(float x, float y);

    void clean();

    void render(Camera &camera);
};


#endif //TALLER_MICROMACHINES_WORLDENTITIES_H
