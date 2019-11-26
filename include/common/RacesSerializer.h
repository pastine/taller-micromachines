
#ifndef TALLER_MICROMACHINES_RACESSERIALIZER_H
#define TALLER_MICROMACHINES_RACESSERIALIZER_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <common/json.h>
#include <common/Serializer.h>
#include <tuple>

class RacesSerializer : public Serializer<std::map<int, std::tuple<int, int>>> {
public:
    JSON serialize_to_json(std::map<int, std::tuple<int, int>> &races) override;
};


#endif //TALLER_MICROMACHINES_RACESSERIALIZER_H
