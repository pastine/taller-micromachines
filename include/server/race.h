#ifndef TALLER_MICROMACHINES_RACE_H
#define TALLER_MICROMACHINES_RACE_H

#include "ClientProxy.h"
#include "player.h"
#include <unordered_map>
#include <string>

class Race :public Thread {
private:
  b2World world;
  std::unordered_map<std::string, Player*> cars;
  bool racing;

public:
  Race();

  virtual void run();

  void add_player(ClientProxy& messenger);

  virtual void stop();

  ~Race();
};


#endif //TALLER_MICROMACHINES_RACE_H
