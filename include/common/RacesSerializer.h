
#ifndef TALLER_MICROMACHINES_RACESSERIALIZER_H
#define TALLER_MICROMACHINES_RACESSERIALIZER_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <common/json.h>
#include <common/Serializer.h>

class RacesSerializer : public Serializer<std::map<int,int>>{
public:
    JSON serialize_to_json(std::map<int,int> &races) override;
};


#endif //TALLER_MICROMACHINES_RACESSERIALIZER_H
