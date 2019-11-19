#ifndef TALLER_MICROMACHINES_PLAYER_H
#define TALLER_MICROMACHINES_PLAYER_H

#include <server/ClientProxy.h>
#include <server/CarHandler.h>
#include <common/Thread.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "StateHandler.h"

class Player : public Thread {
private:
    ClientProxy messenger;
    CarHandler *car;
    bool playing;
    int id;
    int total_laps;
    int partial_laps;
    std::vector<std::vector<float>> flags;
    StateHandler<MoveType> *receiver;
    StateHandler<JSON> *updater;

public:
    Player(ClientProxy messenger, CarHandler *car);

    virtual void run();

    virtual void stop();

    ~Player();

    std::unordered_map<std::string, std::string> get_position();

    void update_status(JSON &status, Track &track);

    std::string getId();

    void update_lap_count();

    void check_progress(int first, int second);

    bool isAlive();
};


#endif //TALLER_MICROMACHINES_PLAYER_H
