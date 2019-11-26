#include <common/CommunicationConstants.h>
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

std::map<std::string, std::tuple<int, int>> ServerProxy::handshake() {
    std::map<std::string, JSON> j = races_serializer.receive(communication);
    std::map<std::string, std::tuple<int, int>> races;
    for (auto &p : j) {
        races.emplace(p.first, std::tuple<int, int>(p.second[J_PLAYERS], p.second[J_MAXPLAYERS]));
    }
    return races;
}

JSON ServerProxy::handshake_answer(int i, std::string playerName, int numPlayers) {
    std::string msg = std::to_string(i);
    this->communication.send_msg(msg);
    this->communication.send_msg(playerName);
    if (i == 0) {
        std::string msg2 = std::to_string(numPlayers);
        this->communication.send_msg(msg2);
    }
    std::string answer;
    this->communication.receive_msg(answer);
    return JSON::parse(answer);
}
