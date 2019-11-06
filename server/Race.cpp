#include "server/Race.h"
#include "server/Player.h"
#include "common/json.h"
#define CENTER "center"
#define CARS "cars"

b2Vec2 gravity(0.0f, 0.0f);
std::atomic_int Race::RaceCount(1);

//AUXILIARY
JSON get_global_status(std::unordered_map<std::string, Player*>& cars) {
  JSON status;
  std::unordered_map<std::string, std::string> center;
  center.emplace("x", "0");
  center.emplace("y", "0");
  JSON j_umap(center);
  status[CENTER] = j_umap;

  JSON car_stats;
  for (auto it = cars.begin(); it != cars.end(); ++it) {
    auto car = it->second->get_position();
    JSON k_umap(car);
    car_stats.push_back(k_umap);
  }
  status[CARS] = car_stats;
  return status;
}

//Race
Race::Race() : id(RaceCount++), world(b2World(gravity)),
               cars(std::unordered_map<std::string, Player*>()),
               racing(true) {
}

void Race::run() {
  while (racing) {
    float32 time = 20.0f / 1000.0f;
    int32 velocity = 6;
    int32 position = 2;
    world.Step(time, velocity, position);
    JSON status = get_global_status(cars);
    for (auto it = cars.begin(); it != cars.end(); ++it) {
      it->second->update_status(status);
    }
    std::chrono::milliseconds tic(20); //20  - delta
    std::this_thread::sleep_for(tic);
  }
}

void Race::add_player(ClientProxy& messenger) {
  Car car((b2World &) world);
  CarHandler handler(car);
  auto* player = new Player(messenger, handler); //pointers when threads?
  player->start();
  cars.emplace(std::to_string(player->getId()), player);
}

void Race::stop() {
  racing = false;
  for ( auto it = cars.begin(); it != cars.end(); ++it ) {
    it->second->stop();
  }
}

Race::~Race() {
  for ( auto it = cars.begin(); it != cars.end(); ++it ) {
    delete(it->second);
  }
  this->join();
}

int Race::getPlayerCount() {
    return cars.size();
}

int Race::getId() {
    return id;
}
