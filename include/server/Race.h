#ifndef TALLER_MICROMACHINES_RACE_H
#define TALLER_MICROMACHINES_RACE_H

#include "ClientProxy.h"
#include "Player.h"
#include "TrackData.h"
#include "State.h"
#include "Environment.h"
#include <unordered_map>
#include <string>
#include <vector>

class Race : public Thread {
    static std::atomic_int RaceCount;

private:
  int id;
  std::unordered_map<int, Player *> players;
  bool racing = true;
  Environment environment;

public:
    explicit Race(char* file);

    virtual void run();

    void add_player(ClientProxy &messenger, std::string name);

    void reaper();

    virtual void stop();

    ~Race();

    int getId();

		TrackData get_track_data();

    int getPlayerCount();

    bool isAlive();

    void add_cars(State &state);
};


#endif //TALLER_MICROMACHINES_RACE_H
