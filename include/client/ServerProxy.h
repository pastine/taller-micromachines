//
// Created by casimiro on 29/10/19.
//

#ifndef TALLER_MICROMACHINES_SERVERPROXY_H
#define TALLER_MICROMACHINES_SERVERPROXY_H

#include "common/MoveType.h"
#include <common/json.h>
#include <common/MoveSerializer.h>
#include <common/StateSerializer.h>
#include <common/Communication.h>
#include <string>
#include <map>
#include <common/RacesSerializer.h>

class ServerProxy {
public:
    ~ServerProxy();
    void player_move(MoveType move);
    void get_game_state(JSON *json);

    ServerProxy(std::string& host, std::string& service);

    std::map<std::string, int> handshake();

    void handshake_answer(int i);

private:
    MoveSerializer move_serializer;
    StateSerializer state_serializer;
    Communication communication;
    RacesSerializer races_serializer;
};


#endif //TALLER_MICROMACHINES_SERVERPROXY_H
