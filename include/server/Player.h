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
#include <queue>

class Player : public Thread {
private:
    ClientProxy messenger;
    CarHandler *car;
    bool playing = true;
    int id;
    size_t total_laps;
    size_t partial_laps;
    StateHandler<MoveType> *receiver;
    StateHandler<State> *updater;
    std::string name;
    std::list<Mod *> mods;
		std::queue<std::vector<float>> flags;
		size_t flag_number;

public:
    Player(ClientProxy messenger, CarHandler *car, std::string name, JSON& flags);

    virtual void run();

    virtual void stop();

    ~Player();

    std::unordered_map<std::string, float> get_position();

    int getId();

    void update_lap_count();

    bool check_progress(std::vector<float>& pos);

    bool isAlive();

    void add_camera(State &state);

    void add_user(State &state);

    void send_update(State &state);

    void remove_mod(Mod &mod);

    std::map<std::string, std::string> get_player_names();

    void add_mod(Mod &mod);
};


#endif //TALLER_MICROMACHINES_PLAYER_H
