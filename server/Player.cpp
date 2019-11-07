#include "server/Player.h"
#define X "x"
#define Y "y"
#define ANGLE "angle"
#define ID "id"

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
    if (car.is_colliding()) {
      car.move(DOWN); //assuming that a collision slows down the car
    }
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
  position.emplace(ID, std::to_string(getId()));
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
