#include "client/ThFrameDrawer.h"
#include "common/CommunicationConstants.h"

#define MULTIPLE (10000.0f)
#define FRAMES_TO_RENDER_MUD 100

ThFrameDrawer::ThFrameDrawer(ProtectedQueue<JSON> *state_queue, JSON &map)
        : state_queue(state_queue) {
    this->done = false;
    this->frames_rendered_mud = 0;

    JSON straight_roads = map[J_TRACKS];
    JSON curved_roads = map[J_CURVED];

    for (auto &straight_road : straight_roads) {
        float x = straight_road[J_X];
        float y = straight_road[J_Y];
        float angle = straight_road[J_ANGLE];
        entities.put(WorldEntities::Entity::STRAIGHT_ROAD,
                     x*MULTIPLE,
                     y*MULTIPLE,
                     angle);
    }

    for (auto &curved_road : curved_roads) {
        float x = curved_road[J_X];
        float y = curved_road[J_Y];
        float angle = curved_road[J_ANGLE];
        entities.put(WorldEntities::Entity::CURVED_ROAD,
                     x*MULTIPLE,
                     y*MULTIPLE,
                     angle);
    }

    JSON muds = map[J_ELEMENTS][J_MUDS];
    for (auto &mud : muds) {
        float x = mud[J_X];
        float y = mud[J_Y];
        entities.put(WorldEntities::Entity::MUD,
                     x*MULTIPLE,
                     y*MULTIPLE);
    }
    JSON oils = map[J_ELEMENTS][J_OILS];
    for (auto &oil : oils) {
        float x = oil[J_X];
        float y = oil[J_Y];
        entities.put(WorldEntities::Entity::OIL,
                     x*MULTIPLE,
                     y*MULTIPLE);
    }
    JSON boulders = map[J_ELEMENTS][J_BOULDERS];
    for (auto &boulder : boulders) {
        float x = boulder[J_X];
        float y = boulder[J_Y];
        entities.put(WorldEntities::Entity::BOULDER,
                     x*MULTIPLE,
                     y*MULTIPLE);
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
        float cam_x = state[J_CENTER][J_X];
        float cam_y = state[J_CENTER][J_Y];
        cam_x *= MULTIPLE;
        cam_y *= MULTIPLE;
        cam.set_center(cam_x, cam_y);

        cam.prepare_frame();
        entities.clean();

        JSON cars = state[J_CARS];
        for (auto &car : cars) {
            float f_x = car[J_X];
            float f_y = car[J_Y];
            entities.put(WorldEntities::Entity::CAR,
                         f_x*MULTIPLE,
                         f_y*MULTIPLE,
                         car[J_ANGLE],
                         car[J_ID],
                         car[J_SPEED]);
        }

        JSON healths = state[J_ELEMENTS][J_HEALTH];
        for (auto &health : healths) {
            float f_x = health[J_X];
            float f_y = health[J_Y];
            entities.put(WorldEntities::Entity::HEART, f_x * MULTIPLE, f_y * MULTIPLE);
        }

        JSON boosts = state[J_ELEMENTS][J_BOOST];
        for (auto &boost : boosts) {
            float f_x = boost[J_X];
            float f_y = boost[J_Y];
            entities.put(WorldEntities::Entity::BOOST, f_x * MULTIPLE, f_y * MULTIPLE);
        }

        entities.render(cam);
        cam.render_car_lives(state[J_USER][J_LIVES]);

        if (state[J_USER][J_MUD]) {
            this->frames_rendered_mud = 1;
        }
        if (this->frames_rendered_mud < FRAMES_TO_RENDER_MUD && this->frames_rendered_mud > 0) {
            cam.render_splatter();
            this->frames_rendered_mud += 1;
        } else {
            this->frames_rendered_mud = 0;
        }

        cam.render_name(state[J_USER][J_NAME]);
        //cam.render_splatter();

        // after rendering everything
        cam.show_frame();
    } catch (std::domain_error &e) {
        std::cout << e.what() << '\n';
    }
}

void ThFrameDrawer::stop() {
    this->done = true;
}

