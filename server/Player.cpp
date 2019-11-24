#include <queue>
#include "server/Player.h"
#include "common/Constants.h"
#include "common/CommunicationConstants.h"
#include "common/ClosedQueueException.h"
#define TILES 8
uint32_t seed;

std::queue<std::vector<float>> prepare_flags(JSON& all) {
	std::cout<<all.size()<<" size of all tracks\n";
	std::queue<std::vector<float>> flags;
	for (auto& pos : all) {
		std::vector<float> new_flag;
		new_flag.emplace_back(pos[J_X]);
		new_flag.emplace_back(pos[J_Y]);
		flags.push(new_flag);
	}
	return flags;
}

Player::Player(ClientProxy messenger, CarHandler *car, std::string name, JSON& flags) :
        messenger(std::move(messenger)), car(car), id(rand_r(&seed) % 9999),
        name(name) {
		this->flags = prepare_flags(flags);
		flag_number = this->flags.size();
		partial_laps = 0;
		total_laps = 0;
    receiver = new StateHandler<MoveType>(&this->messenger);
    updater = new StateHandler<State>(&this->messenger);
    receiver->start();
    updater->start();
}

void Player::run() {
    while (playing) {
        try {
            car->move(receiver->receive());
            update_lap_count();
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
	std::cout<<"partial laps inicial : " << partial_laps<<'\n';
	std::cout<<"total laps inicial : " << total_laps<<'\n';
	std::cout<<"flag_number" <<flag_number<< '\n';
	auto pos = flags.front();
	if(this->check_progress(pos)) {
		flags.pop();
		flags.push(pos);
	}
	if (partial_laps == flag_number) {
		std::cout<<"partial laps : " << partial_laps<<'\n';
		total_laps++;
		partial_laps = 0;
	}
}

bool Player::check_progress(std::vector<float>& pos) {
	std::tuple<float, float, float> car_pos = car->get_position();
	float x = std::get<0>(car_pos);
	float y = std::get<1>(car_pos);
	float x_min = pos[0] - W / 2;
	float x_max = pos[0] + W / 2;
	float y_min = pos[1] - W / 2;
	float y_max = pos[1] + W / 2;
	std::cout<<"posiciones en x: "<<x<<" en y: "<<y<<'\n';
	std::cout<<"posiciones en x_min: "<<x_min<<" en y_min: "<<y_min<<'\n';
	std::cout<<"posiciones en x_max: "<<x_max<<" en y_max: "<<y_max<<'\n';
	if ((x >= x_min && x <= x_max) && (y >= y_min && y <= y_max)) {
	  partial_laps++;
		return true;
  }
	return false;
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
    state.append(J_USER, car->get_crash_state());
}

void Player::send_update(State state) {
    for (auto &m : mods) {
        m->modify_state(state);
    }
    add_camera(state);
    add_user(state);
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
