#ifndef TALLER_MICROMACHINES_PLAYER_H
#define TALLER_MICROMACHINES_PLAYER_H

#include <server/ClientProxy.h>
#include <server/car_handler.h>
#include <common/Thread.h>

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
};


#endif //TALLER_MICROMACHINES_PLAYER_H
