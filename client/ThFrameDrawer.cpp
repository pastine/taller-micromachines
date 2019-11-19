#include "client/ThFrameDrawer.h"
#include "common/CommunicationConstants.h"

#define MULTIPLE 10000.0f

ThFrameDrawer::ThFrameDrawer(ProtectedQueue<JSON> *state_queue, JSON &map)
        : state_queue(state_queue) {
    this->done = false;

    JSON straight_roads = map[J_TRACKS];
    JSON curved_roads = map[J_CURVED];

    for (auto &straight_road : straight_roads) {
        std::string x = straight_road[J_X];
        std::string y = straight_road[J_Y];
        std::string angle = straight_road[J_ANGLE];
        entities.put(WorldEntities::Entity::STRAIGHT_ROAD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y),
                     std::stoi(angle));
    }

    for (auto &curved_road : curved_roads) {
        std::string x = curved_road[J_X];
        std::string y = curved_road[J_Y];
        std::string angle = curved_road[J_ANGLE];
        entities.put(WorldEntities::Entity::CURVED_ROAD,
                     (int) (MULTIPLE * std::stof(x)),
                     (int) (MULTIPLE * std::stof(y)),
                     std::stoi(angle));
    }

    JSON muds = map[J_ELEMENTS][J_MUDS];
    for (auto &mud : muds) {
        std::string x = mud[J_X];
        std::string y = mud[J_Y];
        entities.put(WorldEntities::Entity::MUD,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y));
    }
    JSON oils = map[J_ELEMENTS][J_OILS];
    for (auto &mud : muds) {
        std::string x = mud[J_X];
        std::string y = mud[J_Y];
        entities.put(WorldEntities::Entity::OIL,
                     (int) MULTIPLE * std::stof(x),
                     (int) MULTIPLE * std::stof(y));
    }
    JSON boulders = map[J_ELEMENTS][J_BOULDERS];
    for (auto &mud : muds) {
        std::string x = mud[J_X];
        std::string y = mud[J_Y];
        entities.put(WorldEntities::Entity::BOULDER,
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
        std::string center_x = state[J_CENTER][J_X];
        std::string center_y = state[J_CENTER][J_Y];
        cam.set_center((int) std::stof(center_x) * MULTIPLE, (int) std::stof(center_y) * MULTIPLE);

        cam.prepare_frame();
        entities.clean();

        JSON cars = state[J_CARS];
        for (auto &car : cars) {
            std::string x = car[J_X];
            std::string y = car[J_Y];

            float f_x = std::stof(x.data());
            float f_y = std::stof(y.data());

            f_x *= MULTIPLE;
            f_y *= MULTIPLE;

            std::string angle = car[J_ANGLE];
            std::string playerId = car[J_ID];
            std::string moving = car[J_MOVING];
            entities.put(WorldEntities::Entity::CAR,
                         f_x,
                         f_y,
                         std::stoi(angle),
                         std::stoi(playerId),
                         (bool) std::stoi(moving));
        }

        entities.render(cam);
        std::string lives = state[J_USER][J_LIVES];
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

