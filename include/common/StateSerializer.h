#ifndef TALLER_MICROMACHINES_STATESERIALIZER_H
#define TALLER_MICROMACHINES_STATESERIALIZER_H

#include <common/json.h>
#include <string>
#include <server/State.h>
#include <common/Serializer.h>

class StateSerializer : public Serializer<State> {
public:
    JSON serialize_to_json(State &state) override;
};


#endif //TALLER_MICROMACHINES_STATESERIALIZER_H
