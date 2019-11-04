#include "server/Player.h"
#define X "x"
#define Y "y"
#define ANGLE "angle"

Player::Player(ClientProxy &messenger, CarHandler &car) :
  messenger(std::move(messenger)),
  car(car),
  playing(true) {
}

void Player::run() {
  try {
    while (playing) {
      car.move(messenger.get_move());
      if (car.is_colliding()) {
        car.move(DOWN); //assuming that a collision slows down the car
      }
    }
  } catch (...) {
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
  messenger.send_state(status);
}

Player::~Player() {
  this->join();
}
