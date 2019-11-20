#include "client/ThStateReceiver.h"

ThStateReceiver::ThStateReceiver(ServerProxy *proxy,
                                 ProtectedQueue<JSON> *state_queue) :
        state_queue(state_queue),
        server(proxy) {
    this->done = false;
}

void ThStateReceiver::run() {
    try {
        while (!done) {
            JSON j = this->server->get_game_state();
            this->state_queue->push(std::move(j));
        }
    } catch (std::runtime_error &e) {
        std::cout << "Error in StateHandler -> " << e.what();
    }
}

void ThStateReceiver::stop() {
    this->done = true;
}
