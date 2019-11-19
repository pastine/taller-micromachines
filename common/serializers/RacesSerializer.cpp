
#include "common/RacesSerializer.h"

JSON RacesSerializer::serialize_to_json(std::map<int, int> &races) {
    std::map<std::string, int> ids;
    for (std::pair<const int, int> p : races) {
        ids.insert({std::to_string(p.first), p.second});
    }
    JSON j_races(ids);
    return j_races;
}
