//
// Created by casimiro on 1/11/19.
//

#include "client/ThFrameDrawer.h"
#include <string.h>

#define MULTIPLE 5

ThFrameDrawer::ThFrameDrawer(ProtectedQueue<JSON> *state_queue, JSON& map)
: state_queue(state_queue) {
    this->done = false;

    JSON straight_roads = map["tracks"];
    JSON curved_roads = map["curved"];

    for (JSON::iterator it = straight_roads.begin(); it != straight_roads.end(); ++it) {
        std::string x = (*it)["x"];
        std::string y = (*it)["y"];
        std::string angle = (*it)["angle"];
        entities.put(WorldEntities::Entity::STRAIGHT_ROAD,
                     (int) 35 * std::stof(x),
                     (int) 35 * std::stof(y),
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

    JSON muds = map["elements"]["muds"];
    for (auto & mud : muds) {
        std::string x = mud["x"];
        std::string y = mud["y"];
        entities.put(WorldEntities::Entity::MUD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y));
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
        for (auto & car : cars) {
            std::string x = car["x"];
            std::string y = car["y"];
            std::string angle = car["angle"];
            std::string playerId = car["id"];
            std::string moving = car["moving"];
            entities.put(WorldEntities::Entity::CAR,
                         (int) MULTIPLE * std::stof(x),
                         (int) MULTIPLE * std::stof(y),
                         std::stoi(angle),
                         std::stoi(playerId),
                         (bool)std::stoi(moving));
        }

        /* this is just to test it*/
        entities.put(WorldEntities::Entity::BOOST, 550, -100);
        entities.put(WorldEntities::Entity::HEART, 500, -150);

        entities.render(cam);
        std::string lives = state["elements"]["lives"];
        cam.render_text();
        cam.render_car_lives(std::stoi(lives));

        // after rendering everything
        cam.show_frame();
    } catch (std::domain_error& e) {
        std::cout << e.what() << '\n';
    }
}

void ThFrameDrawer::stop() {
    this->done = true;
}

