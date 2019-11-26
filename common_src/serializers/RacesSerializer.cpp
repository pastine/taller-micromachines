
#include <common/CommunicationConstants.h>
#include "common/RacesSerializer.h"

JSON RacesSerializer::serialize_to_json(std::map<int, std::tuple<int, int>> &races) {
    std::map<std::string, JSON> ids;
    for (auto &p : races) {
        std::map<std::string, int> races_players;
        races_players.emplace(J_PLAYERS, std::get<0>(p.second));
        races_players.emplace(J_MAXPLAYERS, std::get<1>(p.second));
        ids.insert({std::to_string(p.first), races_players});
    }
    JSON j_races(ids);
    return j_races;
}
