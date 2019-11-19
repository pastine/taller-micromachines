#include "server/Race.h"
#include "server/Player.h"
#include "common/json.h"
#include <common/ClosedQueueException.h>
#include <common/CommunicationConstants.h>

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
            JSON status = get_global_status();
            for (auto it = cars.begin(); it != cars.end(); ++it) {
                it->second->update_status(status, track);
            }
            std::chrono::milliseconds tic(20); //20  - delta
            std::this_thread::sleep_for(tic);
        } catch (...) {
            reaper();
            if (!isAlive()) stop();
        }
    }
}

void Race::add_player(ClientProxy messenger) {
    Car *car = new Car(world, cars.size());
    CarHandler *handler = new CarHandler(car);
    auto *player = new Player(std::move(messenger), handler);
    cars.emplace(player->getId(), player);
    player->start();
}

void Race::stop() {
    racing = false;
    for (auto it = cars.begin(); it != cars.end(); ++it)
        it->second->stop();
}

Race::~Race() {
    auto it = cars.begin();
    while (it != cars.end()) {
        delete it->second;
        it = cars.erase(it);
    }
    track.delete_elements();
    this->join();
}

int Race::getPlayerCount() {
    return cars.size();
}

int Race::getId() {
    return id;
}

Track Race::getTrack() {
    return track;
}

void Race::reaper() {
    auto it = cars.begin();
    while (it != cars.end()) {
        if (!it->second->isAlive()) {
            delete it->second;
            it = cars.erase(it);
        } else {
            it++;
        }
    }
}

bool Race::isAlive() {
    return (racing) && (getPlayerCount() > 0);
}

JSON Race::get_global_status() {
    JSON status;
    JSON car_stats;
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        if (!it->second->isAlive()) continue;
        auto car = it->second->get_position();
        JSON k_umap(car);
        car_stats.push_back(k_umap);
    }
    status[J_CARS] = car_stats;
    return status;
}
