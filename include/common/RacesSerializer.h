
#ifndef TALLER_MICROMACHINES_RACESSERIALIZER_H
#define TALLER_MICROMACHINES_RACESSERIALIZER_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <common/json.h>

class RacesSerializer {
public:
    std::string serialize(std::map<int, int> races);

    JSON deserialize(std::string basicString);
};


#endif //TALLER_MICROMACHINES_RACESSERIALIZER_H
