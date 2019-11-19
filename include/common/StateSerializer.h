#ifndef TALLER_MICROMACHINES_STATESERIALIZER_H
#define TALLER_MICROMACHINES_STATESERIALIZER_H

#include <common/json.h>
#include <string>

class StateSerializer {
public:
    std::string serialize(JSON &state);

    JSON deserialize(std::string &serialized_state);
};


#endif //TALLER_MICROMACHINES_STATESERIALIZER_H
