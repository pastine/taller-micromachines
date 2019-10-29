//
// Created by casimiro on 29/10/19.
//

#ifndef TALLER_MICROMACHINES_COMMUNICATION_H
#define TALLER_MICROMACHINES_COMMUNICATION_H


#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

#include "common/Socket.h"
#include "common/MoveType.h"
#include "common/StateSerializer.h"
#include "common/MoveSerializer.h"

class Communication {
public:
    Communication(std::string& host, std::string& service);
    explicit Communication(Socket socket);

    // cant copy the communication
    Communication(const Communication& other) = delete;
    Communication& operator=(const Communication& other) = delete;

    void receive_msg(std::string &msg);
    void send_msg(std::string &msg);

    void shutdown();
private:
    Socket socket;

    StateSerializer state_serializer;

    MoveSerializer move_serializer;
};


#endif //TALLER_MICROMACHINES_COMMUNICATION_H
