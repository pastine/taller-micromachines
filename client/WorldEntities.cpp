//
// Created by casimiro on 26/10/19.
//

#include <tuple>
#include "client/WorldEntities.h"

void WorldEntities::put(WorldEntities::Entity entity, int x, int y,
                        int angle, int id, bool moving) {
    switch (entity) {
        case Entity::CAR:
            car_positions.emplace_back(x, y, angle, id, moving);
            break;
        case Entity::MUD:
            mud_positions.emplace_back(x, y);
            break;
        case Entity::OIL:
            oil_positions.emplace_back(x, y);
            break;
        case Entity::BOULDER:
            boulder_positions.emplace_back(x, y);
            break;
        case Entity::STRAIGHT_ROAD:
            straight_road_positions.emplace_back(x, y, angle);
            break;
        case Entity::CURVED_ROAD:
            curved_road_positions.emplace_back(x, y, angle);
            break;
        case Entity::BOOST:
            boost_positions.emplace_back(x, y);
            break;
        case Entity::HEART:
            heart_positions.emplace_back(x, y);
            break;
    }
}

void WorldEntities::clean() {
    car_positions.clear();
    heart_positions.clear();
    boost_positions.clear();
}

void WorldEntities::render(Camera &camera) {
    for (const std::tuple<int, int, int> &road_pos : straight_road_positions)
        camera.render_object(this->straight_road,
                             std::get<0>(road_pos),
                             std::get<1>(road_pos),
                             std::get<2>(road_pos));

    _render_simple_object(this->boulder_positions, this->boulder, camera);
    _render_simple_object(this->oil_positions, this->oil, camera);
    _render_simple_object(this->mud_positions, this->mud, camera);
    _render_simple_object(this->boost_positions, this->boost, camera);
    _render_simple_object(this->heart_positions, this->heart, camera);


    for (const std::tuple<int, int, int, int, bool> &car_pos : car_positions)
        camera.render_object(this->car,
                             std::get<0>(car_pos),
                             std::get<1>(car_pos),
                             std::get<2>(car_pos),
                             std::get<3>(car_pos),
                             std::get<4>(car_pos));
}

void WorldEntities::_render_simple_object(
        std::vector<std::tuple<int, int>> &positions, Renderizable &object, Camera &camera) {
    for (const std::tuple<int, int> &object_pos : positions)
        camera.render_object(object,
                             std::get<0>(object_pos),
                             std::get<1>(object_pos));
}
