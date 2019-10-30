//
// Created by casimiro on 29/10/19.
//

#ifndef TALLER_MICROMACHINES_STATESERIALIZER_H
#define TALLER_MICROMACHINES_STATESERIALIZER_H

#include <common/json.h>

class StateSerializer {
public:
    std::string serialize(JSON& state);
    JSON deserialize(std::string& serialized_state);
};


#endif //TALLER_MICROMACHINES_STATESERIALIZER_H
