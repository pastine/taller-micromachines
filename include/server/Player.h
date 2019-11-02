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

public:
  Player(ClientProxy& messenger, CarHandler& car);

  virtual void run();

  virtual void stop();

  ~Player();

  void quit();

  std::unordered_map<std::string, std::string> get_position();

  void update_status(JSON &status);
};


#endif //TALLER_MICROMACHINES_PLAYER_H
