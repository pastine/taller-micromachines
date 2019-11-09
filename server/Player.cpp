#include <queue>
#include "server/Player.h"
#define X "x"
#define Y "y"
#define ANGLE "angle"
#define ID "id"

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

Player::Player(ClientProxy &messenger, CarHandler &car) :
  messenger(std::move(messenger)), car(car), playing(true),
  id(rand_r(&seed)), total_laps(0), partial_laps(0),
  flags(std::vector<std::vector<float>>()) {
  add_boundaries(flags);
}

void Player::run() {
  while (playing) {
    car.move(messenger.get_move());
    car.update_surface();
    this->update_lap_count();
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
    std::unordered_map<std::string, std::string> center;
    center.emplace("x", std::to_string(this->car.get_position().x));
    center.emplace("y", std::to_string(this->car.get_position().y));
    JSON j_umap(center);
    status["center"] = j_umap;
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
  float x = car.get_position().x;
  float y = car.get_position().y;
  std::vector<float> min = flags[first];
  std::vector<float> max = flags[second];
  if ((x>= min[0] || x<= min[1]) && (y>= min[0] || y<= min[1])) {
    partial_laps++;
  }
}

Player::~Player() {
  this->join();
}
