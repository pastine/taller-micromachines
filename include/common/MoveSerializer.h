#ifndef TALLER_MICROMACHINES_MOVESERIALIZER_H
#define TALLER_MICROMACHINES_MOVESERIALIZER_H

#include <string>
#include "common/MoveType.h"
#include <common/json.h>
#include <common/Serializer.h>

class MoveSerializer : public Serializer<MoveType> {
public:
    JSON serialize_to_json(MoveType &move) override;

    JSON deserialize(std::string &str) override;
};


#endif //TALLER_MICROMACHINES_MOVESERIALIZER_H
