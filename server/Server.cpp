#include "server/Server.h"
#include "server/ClientProxy.h"

Server::Server(std::string& service) : acceptor(ClientAccepter(service)),
                                       running(true) {
}


void Server::run() {
  while (running){
    try {
      ClientProxy new_client = acceptor.accept_client();
      std::cout<<"New accept!\n";
        std::map<int,int> races_ids_players;
        for (Race* r: races) {
            races_ids_players.insert({r->getId(), r->getPlayerCount()});
        }
      int race_id = new_client.handshake(races_ids_players);
      if (race_id == 0) {
          Race* race = new Race();
          new_client.send_track(race->getTrack());
          races.push_back(race);
          race->start();
          race->add_player(std::move(new_client));
      } else {
          for (Race* r: races) {
              if (r->getId() == race_id) {
                  new_client.send_track(r->getTrack());
                  r->add_player(std::move(new_client));
              }
          }
      }
    } catch(...) {
      break;
    }
  }
}

void Server::stop() {
  running = false;
}

Server::~Server() {
		this->stop();
    acceptor.shutdown();
    auto it = races.begin();
    while (it != races.end()) {
        (*it)->stop();
        delete *it;
        it = races.erase(it);
    }
		this->join();
}


