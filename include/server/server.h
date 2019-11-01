#ifndef TALLER_MICROMACHINES_SERVER_H
#define TALLER_MICROMACHINES_SERVER_H

#include "ClientAccepter.h"
#include "race.h"
#include <string>

class Server {
private:
  ClientAccepter acceptor;
  Race* race; //next: collection of races

public:
  explicit Server(std::string& service);

  void run();

  ~Server();
};


#endif //TALLER_MICROMACHINES_SERVER_H
