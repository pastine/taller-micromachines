
#include "common/RacesSerializer.h"

std::string RacesSerializer::serialize(std::map<int, int> races) {
    std::map<std::string, int> ids;
    for (std::pair<const int, int> p : races) {
        ids.insert({std::to_string(p.first), p.second});
    }
    JSON j_races(ids);
    return j_races.dump();
}

JSON RacesSerializer::deserialize(std::string basicString) {
    return JSON::parse(basicString.data());
}
