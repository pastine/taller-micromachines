#ifndef TALLER_MICROMACHINES_PLAYER_H
#define TALLER_MICROMACHINES_PLAYER_H

#include <server/ClientProxy.h>
#include <server/CarHandler.h>
#include <common/Thread.h>
#include <string>
#include <unordered_map>

class Player : public Thread {
private:
  ClientProxy messenger;
  CarHandler car;
  bool playing;
  int id;

public:
  Player(ClientProxy& messenger, CarHandler& car);

  virtual void run();

  virtual void stop();

  ~Player();

  std::unordered_map<std::string, std::string> get_position();

  void update_status(JSON &status);

    int getId();
};


#endif //TALLER_MICROMACHINES_PLAYER_H
