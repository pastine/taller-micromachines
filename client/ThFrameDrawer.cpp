#include "client/ThFrameDrawer.h"


#define MULTIPLE 10000.0f

ThFrameDrawer::ThFrameDrawer(ProtectedQueue<JSON> *state_queue, JSON &map)
        : state_queue(state_queue) {
    this->done = false;

    JSON straight_roads = map["tracks"];
    JSON curved_roads = map["curved"];

    for (auto &straight_road : straight_roads) {
        std::string x = straight_road["x"];
        std::string y = straight_road["y"];
        std::string angle = straight_road["angle"];
        entities.put(WorldEntities::Entity::STRAIGHT_ROAD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y),
                     std::stoi(angle));
    }

    for (auto &curved_road : curved_roads) {
        std::string x = curved_road["x"];
        std::string y = curved_road["y"];
        std::string angle = curved_road["angle"];
        entities.put(WorldEntities::Entity::CURVED_ROAD,
                     (int) (MULTIPLE * std::stof(x)),
                     (int) (MULTIPLE * std::stof(y)),
                     std::stoi(angle));
    }

    JSON muds = map["elements"]["muds"];
    for (auto &mud : muds) {
        std::string x = mud["x"];
        std::string y = mud["y"];
        entities.put(WorldEntities::Entity::MUD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y));
    }
    JSON oils = map["elements"]["oils"];
    for (auto &mud : muds) {
        std::string x = mud["x"];
        std::string y = mud["y"];
        entities.put(WorldEntities::Entity::MUD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y));
    }
    JSON boulders = map["elements"]["boulders"];
    for (auto &mud : muds) {
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
    } catch (std::runtime_error &e) {
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
        for (auto &car : cars) {
            std::string x = car["x"];
            std::string y = car["y"];

            float f_x = std::stof(x.data());
            float f_y = std::stof(y.data());

            std::cout << "x: " << f_x;
            std::cout << "y: " << f_y << '\n';

            f_x *= MULTIPLE;
            f_y *= MULTIPLE;

            std::string angle = car["angle"];
            std::string playerId = car["id"];
            std::string moving = car["moving"];
            entities.put(WorldEntities::Entity::CAR,
                         f_x,
                         f_y,
                         std::stoi(angle),
                         std::stoi(playerId),
                         (bool) std::stoi(moving));
        }

        entities.render(cam);
        std::string lives = state["user"]["lives"];
        cam.render_car_lives(std::stoi(lives));
        cam.render_text();

        // after rendering everything
        cam.show_frame();
    } catch (std::domain_error &e) {
        std::cout << e.what() << '\n';
    }
}

void ThFrameDrawer::stop() {
    this->done = true;
}

