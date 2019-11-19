#ifndef TALLER_MICROMACHINES_MOVESERIALIZER_H
#define TALLER_MICROMACHINES_MOVESERIALIZER_H

#include <string>
#include "common/MoveType.h"

class MoveSerializer {
public:
    char serialize(MoveType &move);

    MoveType deserialize(std::string move);
};


#endif //TALLER_MICROMACHINES_MOVESERIALIZER_H
