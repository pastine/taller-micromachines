#include "Environment.h"

Environment::Environment() : world({0.0f, 0.0f}),
													 track(Track(world)), limit(Limit(world)) {
	world.SetContactListener(&listener);
}


void Environment::step() {
	float32 time = 1.0f / 30.0f;
	int32 velocity = 6;
	int32 position = 2;
	world.Step(time, velocity, position);
}

std::unordered_map<std::string, std::vector<b2Vec2>> Environment::get_track() {
	return std::move(track.get_static_state());
}

Car* Environment::create_car(unsigned long i) {
	return new Car(world, i);
}

void Environment::get_elements(State &state) {
	state.append(J_ELEMENTS, track.get_elements_state());
}
