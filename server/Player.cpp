#include <queue>
#include "server/Player.h"
#include "common/Constants.h"

uint32_t seed;

void add_boundaries(std::vector<std::vector<float>>& flags) {
  flags.emplace_back(std::vector<float>{-44.5, 75.5});
  flags.emplace_back(std::vector<float>{-35.5, 75.5});
  flags.emplace_back(std::vector<float>{35.5, 75.5});
  flags.emplace_back(std::vector<float>{35.5, 84.5});
  flags.emplace_back(std::vector<float>{35.5, 4.5});
  flags.emplace_back(std::vector<float>{44.5, 4.5});
  flags.emplace_back(std::vector<float>{-35.5, -4.5});
  flags.emplace_back(std::vector<float>{-35.5, 4.5});
}

Player::Player(ClientProxy messenger, CarHandler &car) :
  messenger(std::move(messenger)),
  car(car), playing(true),
  id(rand_r(&seed)), total_laps(0), partial_laps(0),
  flags(std::vector<std::vector<float>>()) {
  add_boundaries(flags);
  receiver = new StateReceiver(&this->messenger);
  receiver->start();
}

void Player::run() {
  while (playing) {
    car.move(receiver->get_move());
    car.update_surface();
    this->update_lap_count();
  }
}

void Player::stop() {
  playing = false;
  receiver->stop();
  messenger.shutdown();
}

std::unordered_map<std::string, std::string> Player::get_position() {
  auto position = car.get_position();
  position.emplace(ANGLE, std::to_string(car.get_angle()));
  position.emplace(ID, std::to_string(getId()));
  return std::move(position);
}

void Player::update_status(JSON& status) {
    JSON j_umap(car.get_position());
    status[CENTER] = j_umap;
    JSON k_umap(car.get_element_state());
    status[ELEMENTS] = k_umap;
    //std::cout<<status.dump(4)<<std::endl;
    messenger.send_state(status); //hilo aparte
}

int Player::getId() {
  return id;
}

void Player::update_lap_count() {
  int first, second;
  switch (partial_laps) {
    case(0): first = 0; second = 1; break;
    case(1): first = 2; second = 3; break;
    case(2): first = 4; second = 5; break;
    case(3): first = 6; second = 7; break;
    case(4): partial_laps = 0; total_laps ++; return;
  }
  this->check_progress(first, second);
}

void Player::check_progress(int first, int second) {
  float x = car.get_x();
  float y = car.get_y();
  std::vector<float> min = flags[first];
  std::vector<float> max = flags[second];
  if ((x>= min[0] || x<= min[1]) && (y>= min[0] || y<= min[1])) {
    partial_laps++;
  }
}

Player::~Player() {
	delete(receiver);
  this->join();
}
