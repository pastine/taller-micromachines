
#ifndef TALLER_MICROMACHINES_STATE_H
#define TALLER_MICROMACHINES_STATE_H

#include <common/json.h>
#include <string>

class State {
public:
    JSON json;

    void append(std::string key, JSON value);
};


#endif //TALLER_MICROMACHINES_STATE_H