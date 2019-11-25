#include "server/Race.h"
#include "server/Player.h"
#include "common/json.h"
#include <common/ClosedQueueException.h>
#include <common/CommunicationConstants.h>
#include <server/State.h>

std::atomic_int Race::RaceCount(1);

Race::Race(char* file) : id(RaceCount++), environment(Environment(file)) {
}

void Race::run() {
    while (racing) {
        try {
        		size_t stopped = 0;
            environment.step();
            State state;
            add_cars(state);
            for (auto & it : players) {
            		auto * player = it.second;
            		if(player->finished()) {stopped++;}
            		environment.get_elements(state);
            		it.second->send_update(state, stopped);
            }
            std::chrono::milliseconds tic(20); //20  - delta
            std::this_thread::sleep_for(tic);
        } catch (...) {
            reaper();
            if (!isAlive()) stop();
        }
    }
}

void Race::add_player(ClientProxy &messenger, std::string name) {
		Car *car = environment.create_car(players.size());
	  CarHandler *handler = new CarHandler(car);
	  JSON aux = environment.get_flag_points();
    Player *player = new Player(std::move(messenger), handler, name, aux);
    players.emplace(player->getId(), player);
    player->start();
}

void Race::stop() {
    racing = false;
    for (auto it = players.begin(); it != players.end(); ++it)
        it->second->stop();
}

Race::~Race() {
    auto it = players.begin();
    while (it != players.end()) {
        delete it->second;
        it = players.erase(it);
    }
    this->join();
}

int Race::getPlayerCount() {
    return players.size();
}

int Race::getId() {
    return id;
}

TrackData Race::get_track_data() {
    return std::move(environment.get_track_data());
}

void Race::reaper() {
    auto it = players.begin();
    while (it != players.end()) {
        if (!it->second->isAlive()) {
            delete it->second;
            it = players.erase(it);
        } else {
            it++;
        }
    }
}

bool Race::isAlive() {
    return (racing) && (getPlayerCount() > 0);
}

void Race::add_cars(State &state) {
    JSON car_stats;
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (!it->second->isAlive()) continue;
        JSON k_umap(it->second->get_position());
        car_stats.push_back(k_umap);
    }
    state.append(J_CARS, car_stats);
}

void Race::toggle_mod(std::string modFileName) {
    if (activatedMods.count(modFileName))
        deactivate_mod(modFileName);
    else
        activate_mod(modFileName);
}

void Race::deactivate_mod(std::string modFileName) {
    Mod *m = activatedMods[modFileName];
    for (auto &p : players)
        p.second->remove_mod(*m);
    activatedMods.erase(modFileName);
}

void Race::activate_mod(std::string modFileName) {
    if (modFileName.empty()) return;
    Mod m(modFileName);
    activatedMods[modFileName] = &m;
    for (auto &p : players)
        p.second->add_mod(*activatedMods[modFileName]);
}
