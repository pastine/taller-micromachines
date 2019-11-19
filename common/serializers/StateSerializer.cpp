#include "common/StateSerializer.h"


JSON StateSerializer::serialize_to_json(State &state) {
    return state.json;
}
