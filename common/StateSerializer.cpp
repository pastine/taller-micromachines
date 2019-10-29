//
// Created by casimiro on 29/10/19.
//

#include "common/StateSerializer.h"

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

std::string StateSerializer::serialize(JSON &state) {
    return state.dump();
}

JSON StateSerializer::deserialize(std::string &serialized_state) {
    return JSON::parse(serialized_state);
}