#include "server/player.h"
#include <vector>

Player::Player(ClientProxy &messenger, CarHandler &car) :
  messenger(std::move(messenger)),
  car(car),
  playing(true) {
}

void Player::run() {
  while (playing) {
    car.move(messenger.get_move());
  }
}

void Player::stop() {
  playing = false;
  this->join();
}

std::vector<std::string> Player::get_position() {
  std::vector<std::string> position;
  position.emplace_back(std::to_string(car.get_position().x));
  position.emplace_back(std::to_string(car.get_position().y));
  position.emplace_back(std::to_string(car.get_angle()));
  return position;
}

void Player::update_status(JSON& status) {
  messenger.send_state(status);
}

Player::~Player() {
}
