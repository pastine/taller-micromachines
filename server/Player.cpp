#include <queue>
#include "server/Player.h"
#include "common/Constants.h"
#include "common/CommunicationConstants.h"
#include "common/ClosedQueueException.h"

uint32_t seed;

void add_boundaries(std::vector<std::vector<float>> &flags) {
    flags.emplace_back(std::vector<float>{-40.0f, 71.75f});
    flags.emplace_back(std::vector<float>{-34.5f, 71.75f});
    flags.emplace_back(std::vector<float>{34.5f, 71.75f});
    flags.emplace_back(std::vector<float>{34.5f, 77.25f});
    flags.emplace_back(std::vector<float>{34.5f, -2.75f});
    flags.emplace_back(std::vector<float>{34.5f, 2.75f});
    flags.emplace_back(std::vector<float>{-34.5f, -2.75f});
    flags.emplace_back(std::vector<float>{-34.5f, 2.75f});
}

Player::Player(ClientProxy messenger, CarHandler *car, std::string name) :
        messenger(std::move(messenger)), car(car), id(rand_r(&seed) % 9999), name(name) {
    add_boundaries(flags);
    receiver = new StateHandler<MoveType>(this->messenger);
    updater = new StateHandler<State>(this->messenger);
    receiver->start();
    updater->start();
}

void Player::run() {
    while (playing) {
        try {
            car->move(receiver->receive());
            car->update_surface();
            this->update_lap_count();
        } catch (...) {
            stop();
        }
    }
}

void Player::stop() {
    playing = false;
    messenger.shutdown();
}

std::unordered_map<std::string, float> Player::get_position() {
    std::unordered_map<std::string, float> position;
    std::tuple<float, float, float> pos = car->get_position();
    position.emplace(J_X, std::get<0>(pos));
    position.emplace(J_Y, std::get<1>(pos));
    position.emplace(J_ANGLE, std::get<2>(pos));
    position.emplace(J_ID, getId());
    position.emplace(J_SPEED, car->get_speed());
    return std::move(position);
}

int Player::getId() {
    return id;
}

void Player::update_lap_count() {
    int first, second;
    switch (partial_laps) {
        case (0):
            first = 0;
            second = 1;
            break;
        case (1):
            first = 2;
            second = 3;
            break;
        case (2):
            first = 4;
            second = 5;
            break;
        case (3):
            first = 6;
            second = 7;
            break;
        case (4):
            partial_laps = 0;
            total_laps++;
            return;
    }
    this->check_progress(first, second);
}

void Player::check_progress(int first, int second) {
    std::tuple<float, float, float> pos = car->get_position();
    float x = std::get<0>(pos);
    float y = std::get<1>(pos);
    std::vector<float> min = flags[first];
    std::vector<float> max = flags[second];
    if ((x >= min[0] || x <= min[1]) && (y >= max[0] || y <= max[1])) {
        partial_laps++;
    }
}

Player::~Player() {
    delete (car);
    delete (receiver);
    delete (updater);
    this->join();
}

bool Player::isAlive() {
    return playing;
}

void Player::add_camera(State &state) {
    std::unordered_map<std::string, float> position;
    std::tuple<float, float, float> pos = car->get_position();
    position.emplace(J_X, std::get<0>(pos));
    position.emplace(J_Y, std::get<1>(pos));
    state.append(J_CENTER, position);
}

void Player::add_user(State &state) {
    state.append(J_USER, car->get_lives());
    state.append(J_USER, car->get_mud_state());
    state.append(J_USER, get_player_names());
}

void Player::send_update(State &state) {
    for (auto &m : mods)
        m->modify_state(state);
    updater->send(state);
}

std::map<std::string, std::string> Player::get_player_names() {
    std::map<std::string, std::string> namemap;
    std::string n = name + "#" + std::to_string(id);
    namemap.emplace(J_NAME, n);
    return namemap;
}

void Player::add_mod(Mod &mod) {
    mods.emplace_back(&mod);
}

void Player::remove_mod(Mod &mod) {
    mods.remove(&mod);
}
