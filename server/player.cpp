#include "server/player.h"

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

Player::~Player() {
}
