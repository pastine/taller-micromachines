//
// Created by casimiro on 1/11/19.
//

#include "client/ThFrameDrawer.h"
#include <string.h>

#define MULTIPLE 5

ThFrameDrawer::ThFrameDrawer(ProtectedQueue *state_queue, JSON& map) : state_queue(state_queue) {
    this->done = false;

    JSON straight_roads = map["straight"];
    JSON curved_roads = map["curved"];

    for (JSON::iterator it = straight_roads.begin(); it != straight_roads.end(); ++it) {
        std::string x = (*it)["x"];
        std::string y = (*it)["y"];
        std::string angle = (*it)["angle"];
        entities.put(WorldEntities::Entity::STRAIGHT_ROAD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y),
                     std::stoi(angle));
    }

    for (JSON::iterator it = curved_roads.begin(); it != curved_roads.end(); ++it) {
        std::string x = (*it)["x"];
        std::string y = (*it)["y"];
        std::string angle = (*it)["angle"];
        entities.put(WorldEntities::Entity::CURVED_ROAD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y),
                     std::stoi(angle));
    }
}

void ThFrameDrawer::run() {
    try {
        while (!this->done) {
            JSON state = this->state_queue->pop();
            this->_draw_frame(state);
        }
    } catch (std::runtime_error& e) {
        std::cout << "Error in FrameDrawer -> " << e.what();
    }
}

void ThFrameDrawer::_draw_frame(JSON &state) {
    try {
        std::string center_x = state["center"]["x"];
        std::string center_y = state["center"]["y"];
        cam.set_center((int) std::stof(center_x) * MULTIPLE, (int) std::stof(center_y) * MULTIPLE);

        cam.prepare_frame();
        entities.clean();

        JSON cars = state["cars"];
        for (JSON::iterator it = cars.begin(); it != cars.end(); ++it) {
            std::string x = (*it)["x"];
            std::string y = (*it)["y"];
            std::string angle = (*it)["angle"];
            std::string playerId = (*it)["id"];
            entities.put(WorldEntities::Entity::CAR,
                         (int) MULTIPLE * std::stof(x),
                         (int) MULTIPLE * std::stof(y),
                         std::stoi(angle),
                         std::stoi(playerId));
        }
        entities.render(cam);
        cam.show_frame();
    } catch (std::domain_error& e) {
        std::cout << e.what() << '\n';
    }
    {}
}

void ThFrameDrawer::stop() {
    this->done = true;
}

