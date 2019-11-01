#include "server/race.h"
#include "server/player.h"
#include "common/json.h"

b2Vec2 gravity(0.0f, 0.0f);

Race::Race() : world(b2World(gravity)) {
}

void Race::run() {
  while (racing) {
    JSON j;
    std::string serializable = "{\"center\": {\"x\": 0, \"y\": 0}, \"cars\":[";
    for (auto it = cars.begin(); it != cars.end(); ++it) {
      auto p = it->second->get_position();
      std::string c;
      c = "{\"x\": " + p[0] + ", \"y\": " + p[1] + ", \"angle\": " + p[2] + "}";
      serializable += c;
    }
    serializable += "]}";
    j = JSON::parse(serializable);
    for (auto player = cars.begin(); player != cars.end(); ++player) {
      player->second->update_status(j);
    }
    //sleep for a tic
  }
}

void Race::add_player(ClientProxy& messenger) {
  Car car((b2World &) world);
  CarHandler handler(car);
  auto* player = new Player(messenger, handler); //pointers when threads?
  //generate id
  std::string s = "test";
  player->start();
  cars.emplace(s, player);
}

void Race::stop() {
  for ( auto it = cars.begin(); it != cars.end(); ++it ) {
    it->second->stop();
  }
}

Race::~Race() {
  this->stop();
  this->join();
}
