#include "client/ServerProxy.h"

ServerProxy::ServerProxy(std::string &host, std::string &service) : communication(host, service) {}


void ServerProxy::player_move(MoveType move) {
    move_serializer.send(communication, move);
}


JSON ServerProxy::get_game_state() {
    return state_serializer.receive(communication);
}

ServerProxy::~ServerProxy() {
    this->communication.shutdown();
}

std::map<std::string, int> ServerProxy::handshake() {
    return races_serializer.receive(communication);
}

JSON ServerProxy::handshake_answer(int i) {
    std::string msg = std::to_string(i);
    this->communication.send_msg(msg);
    std::string answer;
    this->communication.receive_msg(answer);
    return JSON::parse(answer);
}
