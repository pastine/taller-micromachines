#include <queue>
#include "server/Player.h"
#include "common/Constants.h"
#include "common/CommunicationConstants.h"
#include "common/ClosedQueueException.h"
uint32_t seed;

std::queue<std::vector<float>> prepare_flags(JSON& all) {
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
	won = false;
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
	if (won) {return;}
	auto pos = flags.front();
	if(this->check_progress(pos)) {
		flags.pop();
		flags.push(pos);
	}
	if (partial_laps == flag_number) {
		total_laps++;
		partial_laps = 0;
		if (total_laps == LAPS) {
			won = true;
		}
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
	if ((x >= x_min && x <= x_max) && (y >= y_min && y <= y_max)) {
	  partial_laps++;
		return true;
  }
	return false;
}

bool Player::finished() {
	return won;
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

void Player::add_progress(State& state, size_t stopped) {
	std::unordered_map<std::string, bool> progress;
	progress.emplace(J_END, finished());
	if(finished()) {
		progress.emplace(J_POS, stopped);
	}
	state.append(J_USER, progress);
}

void Player::send_update(State state, size_t stopped) {
	for (auto &m : mods) {
			m->modify_state(state);
	}
	add_camera(state);
	add_user(state);
	add_progress(state, stopped);
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

Player::~Player() {
	delete (car);
	delete (receiver);
	delete (updater);
	this->join();
}
