#ifndef TALLER_MICROMACHINES_PLAYER_H
#define TALLER_MICROMACHINES_PLAYER_H

#include <server/ClientProxy.h>
#include <server/CarHandler.h>
#include <common/Thread.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "StateHandler.h"
#include "State.h"
#include "Mod.h"
#include <map>
#include <list>

class Player : public Thread {
private:
    ClientProxy messenger;
    CarHandler *car;
    bool playing = true;
    int id;
    int total_laps = 0;
    int partial_laps = 0;
    std::vector<std::vector<float>> flags;
    StateHandler<MoveType> *receiver;
    StateHandler<State> *updater;
    std::string name;
    std::list<Mod *> mods;

public:
    Player(ClientProxy messenger, CarHandler *car, std::string name);

    virtual void run();

    virtual void stop();

    ~Player();

    std::unordered_map<std::string, float> get_position();

    int getId();

    void update_lap_count();

    void check_progress(int first, int second);

    bool isAlive();

    void add_camera(State &state);

    void add_user(State &state);

    void send_update(State &state);

    void remove_mod(Mod &mod);

    std::map<std::string, std::string> get_player_names();

    void add_mod(Mod &mod);
};


#endif //TALLER_MICROMACHINES_PLAYER_H
