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
#include <memory>
#include <server/State.h>

class Player : public Thread {
private:
    ClientProxy messenger;
    CarHandler *car;
    bool playing = true;
    int id;
    size_t total_laps;
    size_t partial_laps;
    std::unique_ptr<StateHandler<MoveType>> receiver;
		std::unique_ptr<StateHandler<State>> updater;
    std::string name;
    std::list<Mod *> mods;
		std::queue<std::vector<float>> flags;
		size_t flag_number;
		bool won;

public:
    Player(ClientProxy messenger, CarHandler *car, std::string name, JSON& flags);

    virtual void run();

    virtual void stop();

    std::unordered_map<std::string, float> get_position();

    int get_id();

    void update_lap_count();

    bool check_progress(std::vector<float>& pos);

    bool is_alive();

    void add_camera(State &state);

    void add_user(State &state);

    void send_update(State state);

    void remove_mod(Mod &mod);

    std::map<std::string, std::string> get_player_names();

    void add_mod(Mod &mod);
    
    bool finished();

    void add_progress(State &state);

		~Player();

    State prevstate;

    void set_final_pos(size_t i);

    int final_pos = 0;
};


#endif //TALLER_MICROMACHINES_PLAYER_H
