#include "server/Server.h"
#include "server/ClientProxy.h"

Server::Server(std::string& service) : acceptor(ClientAccepter(service)),
                                       race(new Race()) {
  race->start();
}


void Server::run() {
  while (true){
    try {
      ClientProxy new_client = acceptor.accept_client();
      //game options
      race->add_player(new_client);
    } catch(...) {
      break;
    }
  }
}

Server::~Server() {
  delete(race);
}
