#ifndef TALLER_MICROMACHINES_RACE_H
#define TALLER_MICROMACHINES_RACE_H

#include "ClientProxy.h"
#include "Player.h"
#include "Element.h"
#include "State.h"
#include "../../server/Environment.h"
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
    Race();

    virtual void run();

    void add_player(ClientProxy& messenger);

    void reaper();

    virtual void stop();

    ~Race();

    int getId();

		std::unordered_map<std::string, std::vector<b2Vec2>> getTrack();

    int getPlayerCount();

    bool isAlive();

    void add_cars(State &state);
};


#endif //TALLER_MICROMACHINES_RACE_H
