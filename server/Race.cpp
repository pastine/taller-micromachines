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
		size_t stopped = 0;
    while (racing) {
        try {
            State state;
            add_cars(state);
            for (auto & it : players) {
            		auto * player = it.second;
            		if(!player->finished()) {
									environment.get_elements(state);
									it.second->send_update(state, stopped);
									if(player->finished()) {stopped++;}
								}
            }
            std::chrono::milliseconds tic(20);
            std::this_thread::sleep_for(tic);
						environment.step();
        } catch (...) {
            reaper();
            if (!is_alive()) stop();
        }
    }
}

void Race::add_player(ClientProxy &messenger, std::string name) {
		Car *car = environment.create_car(players.size());
	  CarHandler *handler = new CarHandler(car);
	  JSON aux = environment.get_flag_points();
    Player *player = new Player(std::move(messenger), handler, name, aux);
    players.emplace(player->get_id(), player);
    player->start();
}

void Race::stop() {
    racing = false;
    for (auto it = players.begin(); it != players.end(); ++it)
        it->second->stop();
}

int Race::get_player_count() {
    return players.size();
}

int Race::get_id() {
    return id;
}

TrackData Race::get_track_data() {
    return std::move(environment.get_track_data());
}

void Race::reaper() {
    auto it = players.begin();
    while (it != players.end()) {
        if (!it->second->is_alive()) {
            delete it->second;
            it = players.erase(it);
        } else {
            it++;
        }
    }
}

bool Race::is_alive() {
    return (racing) && (get_player_count() > 0);
}

void Race::add_cars(State &state) {
    JSON car_stats;
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (!it->second->is_alive()) continue;
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

Race::~Race() {
	auto it = players.begin();
	while (it != players.end()) {
		delete it->second;
		it = players.erase(it);
	}
	this->join();
}
