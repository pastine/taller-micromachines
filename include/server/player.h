#ifndef TALLER_MICROMACHINES_PLAYER_H
#define TALLER_MICROMACHINES_PLAYER_H

#include <server/ClientProxy.h>
#include <server/car_handler.h>
#include <common/Thread.h>
#include <string>
#include <vector>

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

  std::vector<std::string> get_position();

  void update_status(JSON &status);
};


#endif //TALLER_MICROMACHINES_PLAYER_H
