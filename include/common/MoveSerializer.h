//
// Created by casimiro on 29/10/19.
//

#ifndef TALLER_MICROMACHINES_MOVESERIALIZER_H
#define TALLER_MICROMACHINES_MOVESERIALIZER_H

#include "common/MoveType.h"

class MoveSerializer {
public:
    std::string serialize(MoveType& move);
};


#endif //TALLER_MICROMACHINES_MOVESERIALIZER_H
