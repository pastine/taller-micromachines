#ifndef TALLER_MICROMACHINES_RACE_H
#define TALLER_MICROMACHINES_RACE_H

#include "ClientProxy.h"
#include "Player.h"
#include "TrackData.h"
#include "State.h"
#include "Environment.h"
#include "Mod.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <map>

class Race : public Thread {
    static std::atomic_int RaceCount;

private:
    int id;
    std::unordered_map<int, Player *> players;
    bool racing = true;
    Environment environment;
    int max_players;

public:
    explicit Race(char *file, int i);

    virtual void run();

    void add_player(ClientProxy &messenger, std::string name);

    void reaper();

    virtual void stop();

    int get_id();

    TrackData get_track_data();

    int get_player_count();

    bool is_alive();

    void add_cars_to_state(State &state);

    void toggle_mod(std::string modFileName);

    std::map<std::string, Mod *> activatedMods;

    void deactivate_mod(std::string modFileName);

    void activate_mod(std::string modFileName);

    ~Race();

    int get_max_players();

    bool didnt_start = true;
};


#endif //TALLER_MICROMACHINES_RACE_H
