//
// Created by casimiro on 29/10/19.
//

#ifndef TALLER_MICROMACHINES_COMMUNICATION_H
#define TALLER_MICROMACHINES_COMMUNICATION_H


#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

#include "common/Socket.h"
#include "common/MoveType.h"

class Communication {
public:
    Communication(std::string& host, std::string& service);
    Communication(Socket socket);

    // communication interface
    void send_state(JSON& state);
    void send_move(MoveType& move);
    Communication::MoveType recv_move();
    JSON recv_state();

    // cant copy the communication
    Communication(const Communication& other) = delete;
    Communication& operator=(const Communication& other) = delete;

    shutdown();

private:
    Socket socket;
};


#endif //TALLER_MICROMACHINES_COMMUNICATION_H
