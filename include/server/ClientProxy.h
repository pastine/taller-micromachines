#ifndef TALLER_MICROMACHINES_CLIENTPROXY_H
#define TALLER_MICROMACHINES_CLIENTPROXY_H


#include <common/json.h>
#include <common/MoveType.h>
#include <common/Communication.h>
#include <common/RacesSerializer.h>
#include <common/MoveSerializer.h>
#include <common/StateSerializer.h>
#include <map>
#include <vector>
#include <common/TrackSerializer.h>
#include "Track.h"
#include <string>

class ClientProxy {
public:
    explicit ClientProxy(Communication comm);

    void send_state(State &state);

    MoveType get_move();

    // can't be copied
    ClientProxy &operator=(const ClientProxy &other) = delete;

    ClientProxy(const ClientProxy &other) = delete;

    // movement
    ClientProxy(ClientProxy &&other);

    ClientProxy &operator=(ClientProxy &&other);

    // shutdown communication
    void shutdown();

    ~ClientProxy() {}

    int handshake_get_race(std::map<int, int> races_ids_players);

    void send_track(Track track);

    std::string handshake_get_name(ClientProxy &proxy);

private:
    Communication communication;
    MoveSerializer move_serializer;
    RacesSerializer races_serializer;
    StateSerializer state_serializer;
    TrackSerializer track_serializer;

    void modify_state(State& state);
};


#endif //TALLER_MICROMACHINES_CLIENTPROXY_H
