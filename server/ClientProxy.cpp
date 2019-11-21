#include "server/ClientProxy.h"
#include <dlfcn.h>

ClientProxy::ClientProxy(Communication comm) : communication(std::move(comm)) {}

void ClientProxy::send_state(State &state) {
    modify_state(state);
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

int ClientProxy::handshake_get_race(std::map<int, int> races_ids_players) {
    races_serializer.send(communication, races_ids_players);
    JSON j = races_serializer.receive(communication);
    return std::stoi(j.dump());
}

void ClientProxy::send_track(Track track) {
    track_serializer.send(communication, track);
}

void ClientProxy::modify_state(State& state) {
    void *shared_lib = dlopen("./libAlwaysMud.so", RTLD_NOW);
    typedef char *(*func)(char *);
    func middleman = (func) dlsym(shared_lib, "middleman");
    std::string msg = state.json.dump();
    char *dup_msg = strdup(msg.c_str());
    char *modifiedstr = middleman(dup_msg);
    state = State(modifiedstr);
    free(dup_msg);
    free(modifiedstr);
    dlclose(shared_lib);
}

std::string ClientProxy::handshake_get_name(ClientProxy &proxy) {
    std::string msg;
    this->communication.receive_msg(msg);
    return msg;
}
