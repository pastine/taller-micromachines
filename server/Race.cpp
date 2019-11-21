#include "server/Race.h"
#include "server/Player.h"
#include "common/json.h"
#include <common/ClosedQueueException.h>
#include <common/CommunicationConstants.h>
#include <server/State.h>

std::atomic_int Race::RaceCount(1);

Race::Race() : id(RaceCount++), world({0.0f, 0.0f}),
               track(world), limit(world) {
    world.SetContactListener(&listener);
}

void Race::run() {
    while (racing) {
        try {
            float32 time = 1.0f / 30.0f;
            int32 velocity = 6;
            int32 position = 2;
            world.Step(time, velocity, position);
            State state;
            add_cars(state);
            for (auto it = players.begin(); it != players.end(); ++it) {
                track.add_elements(state);
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

void Race::add_player(ClientProxy &messenger, std::string name) {
    Car *car = new Car(world, players.size());
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
    track.delete_elements();
    this->join();
}

int Race::getPlayerCount() {
    return players.size();
}

int Race::getId() {
    return id;
}

Track Race::getTrack() {
    return track;
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
