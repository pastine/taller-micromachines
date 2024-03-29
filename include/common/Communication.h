#ifndef TALLER_MICROMACHINES_COMMUNICATION_H
#define TALLER_MICROMACHINES_COMMUNICATION_H


#include <common/json.h>
#include "common/Socket.h"
#include "common/MoveType.h"
#include <string>

class Communication {
public:
    Communication();

    Communication(std::string &host, std::string &service);

    explicit Communication(Socket socket);

    // cant copy the communication
    Communication(const Communication &other) = delete;

    Communication &operator=(const Communication &other) = delete;

    // move operations
    Communication(Communication &&other);

    Communication &operator=(Communication &&other);

    void receive_msg(std::string &msg);

    void send_msg(std::string &msg);

    void shutdown();

private:
    Socket socket;
};


#endif //TALLER_MICROMACHINES_COMMUNICATION_H
