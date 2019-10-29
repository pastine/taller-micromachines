//
// Created by casimiro on 29/10/19.
//

#include "ServerProxy.h"

ServerProxy::ServerProxy(std::string &host, std::string &service) : communication(host, service){}


void ServerProxy::player_move(MoveType &move) {
    try {
        std::string msg;
        char _move = this->move_serializer.serialize(move);
        msg.append(&_move);
        this->communication.send_msg(msg);
    } catch (std::runtime_error& e) {
        std::string err = "Error in ServerProxy::player_move -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}


void ServerProxy::get_game_state(JSON *json) {
    try {
        std::string msg;
        this->communication.receive_msg(msg);
        *json = this->state_serializer.deserialize(msg);
    } catch (std::runtime_error& e) {
        std::string err = "Error in ServerProxy::get_game_state -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}