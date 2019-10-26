//
// Created by casimiro on 26/10/19.
//

#include <tuple>
#include "WorldEntities.h"

void WorldEntities::put(WorldEntities::Entity entity, int x, int y, int angle) {
    switch (entity) {
        case Entity::CAR:
            car_positions.emplace_back(x, y, angle);
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
    }
}

void WorldEntities::clean() {
    car_positions.clear();
    boulder_positions.clear();
    mud_positions.clear();
    oil_positions.clear();
}

void WorldEntities::render(Camara &camara) {
    for (const std::tuple<int, int>& boulder_pos : boulder_positions)
        camara.render_object(this->boulder,
                             std::get<0>(boulder_pos),
                             std::get<1>(boulder_pos));

    for (const std::tuple<int, int>& oil_pos : oil_positions)
        camara.render_object(this->oil,
                             std::get<0>(oil_pos),
                             std::get<1>(oil_pos));

    for (const std::tuple<int, int>& mud_pos : mud_positions)
        camara.render_object(this->mud,
                             std::get<0>(mud_pos),
                             std::get<1>(mud_pos));

    for (const std::tuple<int, int, int>& car_pos : car_positions)
        camara.render_object(this->car,
                             std::get<0>(car_pos),
                             std::get<1>(car_pos),
                             std::get<2>(car_pos));
}
