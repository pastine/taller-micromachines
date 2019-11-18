#ifndef TALLER_MICROMACHINES_SERVER_H
#define TALLER_MICROMACHINES_SERVER_H

#include "ClientAccepter.h"
#include "Race.h"
#include <common/Thread.h>
#include <string>
#include <list>
#include <map>

class Server : public Thread {
private:
  ClientAccepter acceptor;
  std::list<Race*> races;
  bool running;

public:
  explicit Server(std::string& service);

  virtual void run();

  virtual void stop();

  ~Server();

    void reaper();
};


#endif //TALLER_MICROMACHINES_SERVER_H
