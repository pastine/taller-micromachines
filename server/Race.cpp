#include "server/Race.h"
#include "server/Player.h"
#include "common/json.h"
#include <common/ClosedQueueException.h>
#include <common/CommunicationConstants.h>
#include <server/State.h>

std::atomic_int Race::RaceCount(1);

Race::Race() : id(RaceCount++), environment(Environment()) {
}

void Race::run() {
    while (racing) {
        try {
            environment.step();
            State state;
            add_cars(state);
            for (auto it = players.begin(); it != players.end(); ++it) {
                environment.get_elements(state);
                it->second->add_camera(state);
                it->second->add_user(state);
                it->second->send_update(state);
            }
            std::chrono::milliseconds tic(20); //20  - delta
            std::this_thread::sleep_for(tic);
        } catch (...) {
            reaper();
            if (!isAlive()) stop();
        }
    }
}

<<<<<<< HEAD
void Race::add_player(ClientProxy& messenger) {
    Car *car = environment.create_car(players.size());
=======
void Race::add_player(ClientProxy &messenger, std::string name) {
    Car *car = new Car(world, players.size());
>>>>>>> b17a4869fe1db94db4c85abf24a35dc027eee986
    CarHandler *handler = new CarHandler(car);
    Player *player = new Player(std::move(messenger), handler, name);
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

std::unordered_map<std::string, std::vector<b2Vec2>> Race::getTrack() {
    return std::move(environment.get_track());
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
