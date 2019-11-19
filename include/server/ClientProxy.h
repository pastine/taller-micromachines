#ifndef TALLER_MICROMACHINES_CLIENTPROXY_H
#define TALLER_MICROMACHINES_CLIENTPROXY_H


#include <common/json.h>
#include <common/MoveType.h>
#include <common/Communication.h>
#include <common/RacesSerializer.h>
#include <map>
#include <vector>
#include <common/TrackSerializer.h>
#include "Track.h"
#include <string>

class ClientProxy {
public:
    explicit ClientProxy(Communication comm);

    void send_state(JSON &state);

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

    // Returns the id of the race to be joined or 0 to create one
    int handshake(std::map<int, int> races_ids_players);

    void send_track(Track track);

private:
    Communication communication;
    MoveSerializer move_serializer;
    RacesSerializer races_serializer;
    StateSerializer state_serializer;
    TrackSerializer track_serializer;

    void modify_state(std::string &basicString);
};


#endif //TALLER_MICROMACHINES_CLIENTPROXY_H
