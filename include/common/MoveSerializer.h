#ifndef TALLER_MICROMACHINES_MOVESERIALIZER_H
#define TALLER_MICROMACHINES_MOVESERIALIZER_H

#include <string>
#include "common/MoveType.h"

class MoveSerializer {
public:
    char serialize(MoveType &move);

    MoveType deserialize(char move);
};


#endif //TALLER_MICROMACHINES_MOVESERIALIZER_H
