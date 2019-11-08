//
// Created by casimiro on 30/10/19.
//

#include "server/ClientProxy.h"

ClientProxy::ClientProxy(Communication comm) : communication(std::move(comm)){}

void ClientProxy::send_state(JSON &state) {
    try {
        std::string msg;
        msg = this->state_serializer.serialize(state);
        this->communication.send_msg(msg);
    } catch (std::runtime_error& e) {
        std::string err = "Error in ClientProxy::send_state -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

MoveType ClientProxy::get_move() {
    try {
        std::string msg;
        this->communication.receive_msg(msg);
        MoveType move = this->move_serializer.deserialize(msg.data()[0]);
        return move;
    } catch (std::runtime_error& e) {
        std::string err = "Error in ClientProxy::get_move -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

ClientProxy &ClientProxy::operator=(ClientProxy &&other) {
    if (this == &other) return *this;
    this->communication = std::move(other.communication);
    return *this;
}

ClientProxy::ClientProxy(ClientProxy &&other) {
    this->communication = std::move(other.communication);
}

void ClientProxy::shutdown() {
  this->communication.shutdown();
}

int ClientProxy::handshake(std::map<int,int> races_ids_players) {
    try {
        std::string msg;
        msg = this->races_serializer.serialize(races_ids_players);
        this->communication.send_msg(msg);

        std::string response;
        this->communication.receive_msg(response);
        return stoi(response);
    } catch (std::runtime_error& e) {
        std::string err = "Error in ClientProxy::handshake -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}




