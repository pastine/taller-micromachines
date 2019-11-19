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

Player::Player(ClientProxy messenger, CarHandler *car) :
        messenger(std::move(messenger)),
        car(car), playing(true),
        id(rand_r(&seed) % 9999), total_laps(0), partial_laps(0) {
    add_boundaries(flags);
    receiver = new StateHandler<MoveType>(this->messenger);
    updater = new StateHandler<JSON>(this->messenger);
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

std::unordered_map<std::string, std::string> Player::get_position() {
    std::unordered_map<std::string, std::string> position;
    std::tuple<float, float, float> pos = car->get_position();
    position.emplace(J_X, std::to_string(std::get<0>(pos)));
    position.emplace(J_Y, std::to_string(std::get<1>(pos)));
    position.emplace(J_ANGLE, std::to_string(std::get<2>(pos)));
    position.emplace(J_ID, getId());
    position.emplace(J_MOVING, std::to_string(car->isMoving()));
    return std::move(position);
}

void Player::update_status(JSON &status, Track &track) {
    std::unordered_map<std::string, std::string> position;
    std::tuple<float, float, float> pos = car->get_position();
    position.emplace(J_X, std::to_string(std::get<0>(pos)));
    position.emplace(J_Y, std::to_string(std::get<1>(pos)));
    JSON j_umap(position);
    status[J_CENTER] = j_umap;
    JSON k_umap(car->get_user_state());
    status[J_USER] = k_umap;
    JSON l_umap(track.get_elements_state());
    status[J_ELEMENTS] = l_umap;
    updater->send(status);
}

std::string Player::getId() {
    return std::to_string(id);
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
