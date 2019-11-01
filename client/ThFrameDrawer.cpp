//
// Created by casimiro on 1/11/19.
//

#include "ThFrameDrawer.h"

ThFrameDrawer::ThFrameDrawer(ProtectedQueue *state_queue) : state_queue(state_queue) {}

void ThFrameDrawer::run() {
    try {
        while (true) {
            JSON state = this->state_queue->pop();
            this->_draw_frame(state);
        }
    } catch (std::runtime_error& e) {
        std::cout << "Error in FrameDrawer -> " << e.what();
    }
}

void ThFrameDrawer::_draw_frame(JSON &state) {
    cam.set_center(state["center"]["x"], state["center"]["y"]);

    cam.prepare_frame();
    entities.clean();

    JSON cars = state["car"];
    for (JSON::iterator it = cars.begin(); it != cars.end(); ++it) {
        entities.put(WorldEntities::Entity::CAR, (*it)["x"], (*it)["y"], (*it)["angle"]);
    }

    entities.render(cam);
}

