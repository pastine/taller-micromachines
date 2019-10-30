//
// Created by casimiro on 29/10/19.
//

#ifndef TALLER_MICROMACHINES_SERVERPROXY_H
#define TALLER_MICROMACHINES_SERVERPROXY_H

#include "../include/common/MoveType.h"
#include <common/json.h>
#include <common/MoveSerializer.h>
#include <common/StateSerializer.h>
#include <common/Communication.h>


class ServerProxy {
public:
    void player_move(MoveType& move);
    void get_game_state(JSON *json);

    ServerProxy(std::string& host, std::string& service);
private:
    MoveSerializer move_serializer;
    StateSerializer state_serializer;
    Communication communication;
};


#endif //TALLER_MICROMACHINES_SERVERPROXY_H
