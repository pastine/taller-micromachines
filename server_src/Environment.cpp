#include "server/Consumable.h"
#include "server/Environment.h"

Environment::Environment(char *file) : world({0.0f, 0.0f}),
                                       track(Track(&world, file)),
                                       limit(Limit(world)) {
    world.SetContactListener(&listener);
}

void Environment::step() {
    float32 time = 1.0f / 30.0f;
    int32 velocity = 6;
    int32 position = 2;
    world.Step(time, velocity, position);
    auto to_remove = track.get_removable_elements();
    while (!to_remove.empty()) {
        delete (to_remove.back());
        to_remove.pop_back();
    }
}

TrackData Environment::get_track_data() {
    return std::move(track.get_static_data());
}

Car *Environment::create_car(unsigned long i) {
    return new Car(world, i);
}

void Environment::get_elements(State &state) {
    state.append(J_ELEMENTS, track.get_elements_state());
}

JSON Environment::get_flag_points() {
    return track.get_straight_points();
}
