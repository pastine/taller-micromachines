#include <dirent.h>
#include "server/Server.h"
#include "server/ClientProxy.h"

Server::Server(std::string &service, char *file) : acceptor(service), track_file(file) {
    load_mods();
}

void Server::run() {
    while (running) {
        try {
            ClientProxy new_client = acceptor.accept_client();
            std::cout << "New accept!\n";
            reaper();
            int race_id = handshake_get_race(new_client);
            std::string name = new_client.handshake_get_name();
            if (race_id == 0) {
                int players = new_client.handshake_get_players();
                create_race(new_client, name, players);
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

void Server::reaper() {
    auto it = races.begin();
    while (it != races.end()) {
        (*it)->reaper();
        if (!(*it)->is_alive()) {
            (*it)->stop();
            delete *it;
            it = races.erase(it);
        } else {
            it++;
        }
    }
}

void Server::create_race(ClientProxy &proxy, std::string name, int i) {
    Race *race = new Race(track_file, i);
    auto aux = race->get_track_data();
    proxy.send_track(aux);
    races.push_back(race);
    race->start();
    race->add_player(proxy, name);
}

void Server::add_player_to_race(ClientProxy &new_client, int id, std::string name) {
    for (Race *race: races) {
        if (race->get_id() == id) {
            auto aux = race->get_track_data();
            new_client.send_track(aux);
            race->add_player(new_client, name);
        }
    }
}

int Server::handshake_get_race(ClientProxy &new_client) {
    std::map<int, std::tuple<int, int>> races_ids_players;
    for (Race *r: races)
        races_ids_players.insert({r->get_id(), {r->get_player_count(), r->get_max_players()}});
    return new_client.handshake_get_race(races_ids_players);
}

void Server::print_mods() {
    std::cout << "Available Mods: \n";
    std::cout << "(input the number to activate them)\n";
    for (auto &p : mods)
        std::cout << "\t" << p.first << ": " << p.second << "\n";
}

void Server::toggle_mod(int i) {
    for (Race *r: races)
        r->toggle_mod(mods[i]);
}

void Server::load_mods() {
    DIR *modsDir = opendir("server/mods/");
    if (!modsDir) return;
    struct dirent *ent;
    int counter = 1;
    while ((ent = readdir(modsDir)) != NULL) {
        std::string name = ent->d_name;
        if (name == "." || name == "..") continue;
        mods.insert({counter++, name});
    }
    closedir(modsDir);
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
