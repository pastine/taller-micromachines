#include "server/Player.h"
#define X "x"
#define Y "y"
#define ANGLE "angle"

uint32_t seed;

Player::Player(ClientProxy &messenger, CarHandler &car) :
  messenger(std::move(messenger)),
  car(car),
  playing(true),
  id(rand_r(&seed)) {
}

void Player::run() {
  while (playing) {
    car.move(messenger.get_move()); //
    car.update_surface();
  }
}

void Player::stop() {
  playing = false;
  messenger.shutdown();
}

std::unordered_map<std::string, std::string> Player::get_position() {
  std::unordered_map<std::string, std::string> position;
  position.emplace(X, std::to_string(car.get_position().x));
  position.emplace(Y, std::to_string(car.get_position().y));
  position.emplace(ANGLE, std::to_string(car.get_angle()));
  return std::move(position);
}

void Player::update_status(JSON& status) {
  messenger.send_state(status); //hilo aparte
}

Player::~Player() {
  this->join();
}

int Player::getId() {
    return id;
}
