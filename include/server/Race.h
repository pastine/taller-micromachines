#ifndef TALLER_MICROMACHINES_RACE_H
#define TALLER_MICROMACHINES_RACE_H

#include "ClientProxy.h"
#include "Player.h"
#include "ContactListener.h"
#include "Track.h"
#include "Element.h"
#include "Limit.h"
#include "State.h"
#include <unordered_map>
#include <string>
#include <vector>

class Race : public Thread {
    static std::atomic_int RaceCount;

private:
  int id;
  b2World world;
	Track track;
    std::unordered_map<std::string, Player *> players;
    bool racing = true;
  ContactListener listener;
  Limit limit;

public:
    Race();

    virtual void run();

    void add_player(ClientProxy messenger);

    void reaper();

    virtual void stop();

    ~Race();

    int getId();

    Track getTrack();

    int getPlayerCount();

    bool isAlive();

    void add_cars(State &state);
};


#endif //TALLER_MICROMACHINES_RACE_H
