//
// Created by casimiro on 29/10/19.
//

#include "client/ServerProxy.h"

ServerProxy::ServerProxy(std::string &host, std::string &service) : communication(host, service){}


void ServerProxy::player_move(MoveType move) {
    try {
        std::string msg;
        char _move = this->move_serializer.serialize(move);
        msg.append(&_move);
        this->communication.send_msg(msg);
        std::cout << "sent: " << msg << '\n';
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
        std::cout << msg.data() << "\n";
        *json = this->state_serializer.deserialize(msg);
    } catch (std::runtime_error& e) {
        std::string err = "Error in ServerProxy::get_game_state -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

ServerProxy::~ServerProxy() {
    this->communication.shutdown();
}

std::map<std::string, int> ServerProxy::handshake() {
    try {
        std::string msg;
        this->communication.receive_msg(msg);
        JSON j = this->races_serializer.deserialize(msg);
        return j.get<std::map<std::string, int>>();
    } catch (std::runtime_error& e) {
        std::string err = "Error in ServerProxy::handshake -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

void ServerProxy::handshake_answer(int i, JSON* map) {
    try {
        std::string msg = std::to_string(i);
        this->communication.send_msg(msg);
        this->communication.receive_msg(msg);
        *map = JSON::parse(msg);
    } catch (std::runtime_error& e) {
        std::string err = "Error in ServerProxy::handshake_answer -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}
