
#ifndef TALLER_MICROMACHINES_MOD_H
#define TALLER_MICROMACHINES_MOD_H


#include <string>
#include "State.h"

class Mod {
public:
    explicit Mod(std::string fileName);

    ~Mod();

    void modify_state(State &state);

    void *shared_lib;
};


#endif //TALLER_MICROMACHINES_MOD_H
