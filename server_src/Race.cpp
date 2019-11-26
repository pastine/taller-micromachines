#include "server/Race.h"
#include "server/Player.h"
#include "common/json.h"
#include <common/ClosedQueueException.h>
#include <common/CommunicationConstants.h>
#include <server/State.h>

std::atomic_int Race::RaceCount(1);

Race::Race(char *file, int i) : id(RaceCount++), environment(Environment(file)), max_players(i) {
}

void Race::run() {
    size_t stopped = 0;
    while (racing) {
        try {
            State state;
            if (!didnt_start)
                environment.step();
            add_cars_to_state(state);
            for (auto &it : players) {
                auto *player = it.second;
                environment.get_elements(state);
                player->send_update(state);
                if (player->finished())
                    player->set_final_pos(stopped++);
            }
            std::chrono::milliseconds tic(20);
            std::this_thread::sleep_for(tic);
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
    if (players.size() == (uint) max_players) didnt_start = false;
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

void Race::add_cars_to_state(State &state) {
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
    for (auto &p : players) {
        p.second->remove_mod(m);
    }
    delete activatedMods[modFileName];
    activatedMods.erase(modFileName);
}

void Race::activate_mod(std::string modFileName) {
    if (modFileName.empty()) return;
    Mod *m = new Mod(modFileName);
    activatedMods[modFileName] = m;
    for (auto &p : players)
        p.second->add_mod(activatedMods[modFileName]);
}

Race::~Race() {
    auto it = players.begin();
    while (it != players.end()) {
        delete it->second;
        it = players.erase(it);
    }
    for (auto &m : activatedMods) {
        delete m.second;
        activatedMods.erase(m.first);
    }
    this->join();
}

int Race::get_max_players() {
    return max_players;
}
