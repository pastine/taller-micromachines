#ifndef TALLER_MICROMACHINES_RACE_H
#define TALLER_MICROMACHINES_RACE_H

#include "ClientProxy.h"
#include "Player.h"
#include "ContactListener.h"
#include "Track.h"
#include "Element.h"
#include <unordered_map>
#include <string>
#include <vector>

class Race :public Thread {
  static std::atomic_int RaceCount;

private:
  int id;
  b2World world;
	Track track;
  std::unordered_map<std::string, Player*> cars;
  std::vector<Element*> elements;
  bool racing;
  ContactListener listener;

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

    JSON get_global_status();
    bool isAlive();
};


#endif //TALLER_MICROMACHINES_RACE_H
