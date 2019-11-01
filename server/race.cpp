#include "server/race.h"
#include "server/player.h"

b2Vec2 gravity(0.0f, 0.0f);

Race::Race() : world(b2World(gravity)) {
}

void Race::run() {
  while (racing) {
    for (auto it = cars.begin(); it != cars.end(); ++it) {
      //save data in json;
    }
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
