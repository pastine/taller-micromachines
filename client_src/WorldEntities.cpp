#include <tuple>
#include "client/WorldEntities.h"

void WorldEntities::put(WorldEntities::Entity entity, float x, float y,
                        float angle, int id, float speed) {
    switch (entity) {
        case Entity::CAR:
            car_positions.emplace_back(x, y, angle, id, speed);
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
    for (const std::tuple<float, float, float> &road_pos : straight_road_positions) {
        camera.render_object(this->straight_road,
                             std::get<0>(road_pos),
                             std::get<1>(road_pos),
                             std::get<2>(road_pos));
    }

    for (const std::tuple<float, float, float> &road_pos : curved_road_positions) {
        camera.render_object(this->curved_road,
                             std::get<0>(road_pos),
                             std::get<1>(road_pos),
                             std::get<2>(road_pos));
    }

    _render_simple_object(this->boulder_positions, this->boulder, camera);
    _render_simple_object(this->oil_positions, this->oil, camera);
    _render_simple_object(this->mud_positions, this->mud, camera);
    _render_simple_object(this->boost_positions, this->boost, camera);
    _render_simple_object(this->heart_positions, this->heart, camera);


    for (const std::tuple<float, float, float, float, float> &car_pos : car_positions)
        camera.render_object(this->car,
                             std::get<0>(car_pos),
                             std::get<1>(car_pos),
                             std::get<2>(car_pos),
                             std::get<3>(car_pos),
                             std::get<4>(car_pos));

    for (size_t i = 0; i < this->explotion_positions.size(); ++i) {
        std::tuple<Explotion, float, float> item = explotion_positions.front();
        camera.render_object(std::get<0>(item), std::get<1>(item), std::get<2>(item));
        explotion_positions.pop();
        if (!std::get<0>(item).is_done())
            explotion_positions.push(item);
    }
}

void WorldEntities::_render_simple_object(
        std::vector<std::tuple<float, float>> &positions, Renderizable &object, Camera &camera) {
    for (const std::tuple<float, float> &object_pos : positions)
        camera.render_object(object,
                             std::get<0>(object_pos),
                             std::get<1>(object_pos));
}

void WorldEntities::put_explotion(float x, float y) {
    Explotion explotion;
    explotion_positions.push(std::tuple<Explotion, float, float>(explotion, x, y));
}
