
#include "server/State.h"
#include <unordered_map>

void State::insert(std::string key, JSON value) {
    json[key] = value;
}

void State::append(std::string key, JSON value) {
    if (json[key].empty()) return insert(key, value);
    std::unordered_map<std::string, JSON> prevval = json[key];
    std::unordered_map<std::string, JSON> newvalue = value;
    prevval.insert(newvalue.begin(), newvalue.end());
    json[key] = prevval;
}

State::State(std::string str) : json(JSON::parse(str)) {}

bool State::operator==(const State &other) const {
    auto x = this->json.dump();
    auto y = other.json.dump();
    return x == y;
}
