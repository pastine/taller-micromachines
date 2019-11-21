#include "server/ClientProxy.h"
#include <dlfcn.h>

ClientProxy::ClientProxy(Communication comm) : communication(std::move(comm)) {}

void ClientProxy::send_state(State &state) {
//    modify_state(msg);
    state_serializer.send(communication, state);
}

MoveType ClientProxy::get_move() {
    return move_serializer.receive(communication);
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

int ClientProxy::handshake(std::map<int, int> races_ids_players) {
    races_serializer.send(communication, races_ids_players);
    JSON j = races_serializer.receive(communication);
    return std::stoi(j.dump());
}

void ClientProxy::send_track(
				std::unordered_map<std::string, std::vector<b2Vec2>>& track) {
    track_serializer.send(communication, track);
}

void ClientProxy::modify_state(std::string &msg) {
    void *shared_lib = dlopen("./libMiddleManState.so", RTLD_NOW);
    typedef char *(*func)(char *);
    func middleman = (func) dlsym(shared_lib, "middleman");
    char *dup_msg = strdup(msg.c_str());
    char *modifiedstr = middleman(dup_msg);
    msg = std::string(modifiedstr);
    free(dup_msg);
    free(modifiedstr);
    dlclose(shared_lib);
}
