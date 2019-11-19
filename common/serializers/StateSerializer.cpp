#include "common/StateSerializer.h"
#include <common/json.h>


std::string StateSerializer::serialize(JSON &state) {
    return state.dump();
}

JSON StateSerializer::deserialize(std::string &serialized_state) {
    return JSON::parse(serialized_state.data());
}
