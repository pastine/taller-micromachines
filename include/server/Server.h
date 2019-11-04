#ifndef TALLER_MICROMACHINES_SERVER_H
#define TALLER_MICROMACHINES_SERVER_H

#include "ClientAccepter.h"
#include "Race.h"
#include <common/Thread.h>
#include <string>

class Server : public Thread {
private:
  ClientAccepter acceptor;
  Race* race; //next: collection of races
  bool running;

public:
  explicit Server(std::string& service);

  virtual void run();

  virtual void stop();

  ~Server();
};


#endif //TALLER_MICROMACHINES_SERVER_H
