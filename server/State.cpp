
#include "server/State.h"

void State::append(std::string key, JSON value) {
    json[key] = value;
}
