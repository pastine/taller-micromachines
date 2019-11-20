#include "server/Server.h"
#include "server/ClientProxy.h"

Server::Server(std::string &service) : acceptor(service) {}

void Server::run() {
    while (running) {
        try {
            ClientProxy new_client = acceptor.accept_client();
            std::cout << "New accept!\n";
            reaper();
            int race_id = handshake(new_client);
            if (race_id == 0) {
                create_race(new_client);
            } else {
                add_player_to_race(new_client, race_id);
            }
        } catch (...) {
            stop();
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

void Server::reaper() {
    auto it = races.begin();
    while (it != races.end()) {
        (*it)->reaper();
        if (!(*it)->isAlive()) {
            (*it)->stop();
            delete *it;
            it = races.erase(it);
        } else {
            it++;
        }
    }
}

void Server::create_race(ClientProxy &new_client) {
    Race *race = new Race();
    new_client.send_track(race->getTrack());
    races.push_back(race);
    race->start();
    race->add_player(new_client);
}

void Server::add_player_to_race(ClientProxy &new_client, int id) {
    for (Race *r: races) {
        if (r->getId() == id) {
            new_client.send_track(r->getTrack());
            r->add_player(new_client);
        }
    }
}

int Server::handshake(ClientProxy &new_client) {
    std::map<int, int> races_ids_players;
    for (Race *r: races) {
        races_ids_players.insert({r->getId(), r->getPlayerCount()});
    }
    return new_client.handshake(races_ids_players);
}
