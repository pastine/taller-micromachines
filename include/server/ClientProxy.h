//
// Created by casimiro on 30/10/19.
//

#ifndef TALLER_MICROMACHINES_CLIENTPROXY_H
#define TALLER_MICROMACHINES_CLIENTPROXY_H


#include <common/json.h>
#include <common/MoveType.h>
#include <common/Communication.h>

class ClientProxy {
public:
    ClientProxy(Communication comm);
    void send_state(JSON& state);
    MoveType get_move();

    // can't be copied
    ClientProxy& operator=(const ClientProxy& other) = delete;
    ClientProxy(const ClientProxy& other) = delete;

    // movement
    ClientProxy(ClientProxy&& other);
    ClientProxy& operator=(ClientProxy&& other);

private:
    Communication communication;
    MoveSerializer move_serializer;
    StateSerializer state_serializer;
};


#endif //TALLER_MICROMACHINES_CLIENTPROXY_H
