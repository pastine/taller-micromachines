//
// Created by casimiro on 1/11/19.
//

#include "client/ThStateReceiver.h"

ThStateReceiver::ThStateReceiver(ServerProxy *proxy,
                                 ProtectedQueue *state_queue) :
                                 state_queue(state_queue),
                                 server(proxy) {
    this->done = false;
}

void ThStateReceiver::run() {
    JSON state;
    try {
        while (!done) {
            this->server->get_game_state(&state);
            this->state_queue->push(std::move(state));
        }
    } catch (std::runtime_error& e) {
        std::cout << "Error in StateReceiver -> " << e.what();
    }
}

void ThStateReceiver::stop() {
    this->done = true;
}
