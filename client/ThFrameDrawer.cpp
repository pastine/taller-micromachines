//
// Created by casimiro on 1/11/19.
//

#include "client/ThFrameDrawer.h"

ThFrameDrawer::ThFrameDrawer(ProtectedQueue *state_queue) : state_queue(state_queue) {
    this->done = false;
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
    /*try {
        cam.set_center((int) state["center"]["x"],(int) state["center"]["y"]);

        cam.prepare_frame();
        entities.clean();

        JSON cars = state["cars"];
        for (JSON::iterator it = cars.begin(); it != cars.end(); ++it) {
            entities.put(WorldEntities::Entity::CAR,
                        (int) (*it)["x"],
                        (int) (*it)["y"],
                        (int) (*it)["angle"]);
        }

        entities.render(cam);
    } catch (std::domain_error& e) {
        //std::cout << e.what() << '\n';
    }*/
    {}
}

void ThFrameDrawer::stop() {
    this->done = true;
}

