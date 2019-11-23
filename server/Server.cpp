#include "server/Server.h"
#include "server/ClientProxy.h"

Server::Server(std::string &service, char* file) : acceptor(service),
																									 track_file(file) {
}

void Server::run() {
    while (running) {
        try {
            ClientProxy new_client = acceptor.accept_client();
            std::cout << "New accept!\n";
            reaper();
            int race_id = handshake_get_race(new_client);
            std::string name = new_client.handshake_get_name(new_client);
            if (race_id == 0) {
                create_race(new_client, name);
            } else {
                add_player_to_race(new_client, race_id, name);
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

void Server::create_race(ClientProxy &new_client, std::string name) {
    Race *race = new Race(track_file);
    auto aux = race->get_track_data();
    new_client.send_track(aux);
    races.push_back(race);
    race->start();
    race->add_player(new_client, name);
}

void Server::add_player_to_race(ClientProxy &new_client, int id, std::string name) {
    for (Race *race: races) {
        if (race->getId() == id) {
        		auto aux = race->get_track_data();
            new_client.send_track(aux);
            race->add_player(new_client, name);
        }
    }
}

int Server::handshake_get_race(ClientProxy &new_client) {
    std::map<int, int> races_ids_players;
    for (Race *r: races) {
        races_ids_players.insert({r->getId(), r->getPlayerCount()});
    }
    return new_client.handshake_get_race(races_ids_players);
}
