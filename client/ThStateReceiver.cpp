//
// Created by casimiro on 1/11/19.
//

#include "client/ThStateReceiver.h"

ThStateReceiver::ThStateReceiver(ServerProxy *proxy,
                                 ProtectedQueue *state_queue) :
                                 state_queue(state_queue),
                                 server(proxy) {}

void ThStateReceiver::run() {
    JSON state;
    bool done = false;
    try {
        while (!done) {
            this->server->get_game_state(&state);
            this->state_queue->push(std::move(state));
        }
    } catch (std::runtime_error& e) {
        std::cout << "Error in StateReceiver -> " << e.what();
    }
}
