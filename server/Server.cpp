#include "server/Server.h"
#include "server/ClientProxy.h"

Server::Server(std::string& service) : acceptor(ClientAccepter(service)),
                                       race(new Race()),
                                       running(true) {
  race->start();
}


void Server::run() {
  while (running){
    try {
      ClientProxy new_client = acceptor.accept_client();
      std::cout<<"New accept!\n";
      //game options
      race->add_player(new_client);
    } catch(...) {
      break;
    }
  }
}

void Server::stop() {
  running = false;
}

Server::~Server() {
  race->stop();
  acceptor.shutdown();
  this->join();
  delete(race);
}


