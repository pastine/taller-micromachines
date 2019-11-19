#include <common/json.h>
#include <unordered_map>
#include <server/Oil.h>
#include "common/TrackSerializer.h"
#include "common/Constants.h"
#include "common/CommunicationConstants.h"

JSON TrackSerializer::serialize_to_json(Track &track) {
    JSON all;
    JSON aux;
    JSON aux_elements;
    for (float i = FIRST_GROUND_TILE_X; i < 31.05; i += (W - 2)) {
        std::unordered_map<std::string, std::string> ground;
        ground.emplace(J_X, std::to_string(i));
        ground.emplace(J_Y, std::to_string(FIRST_GROUND_TILE_Y));
        ground.emplace(J_ANGLE, std::to_string(FIRST_GROUND_TILE_ANGLE));
        JSON j_umap(ground);
        aux.push_back(j_umap);
        std::unordered_map<std::string, std::string> ceiling;
        ceiling.emplace(J_X, std::to_string(i));
        ceiling.emplace(J_Y, std::to_string(FIRST_CEILING_TILE_Y));
        ceiling.emplace(J_ANGLE, std::to_string(FIRST_CEILING_TILE_ANGLE));
        JSON k_umap(ceiling);
        aux.push_back(k_umap);
    }

    for (float i = FIRST_LEFT_TILE_Y; i < 69; i += (W - 2)) {
        std::unordered_map<std::string, std::string> left;
        left.emplace(J_X, std::to_string(FIRST_LEFT_TILE_X));
        left.emplace(J_Y, std::to_string(i));
        left.emplace(J_ANGLE, std::to_string(FIRST_LEFT_TILE_ANGLE));
        JSON j_umap(left);
        aux.push_back(j_umap);
        std::unordered_map<std::string, std::string> right;
        right.emplace(J_X, std::to_string(FIRST_RIGHT_TILE_X));
        right.emplace(J_Y, std::to_string(i));
        right.emplace(J_ANGLE, std::to_string(FIRST_RIGHT_TILE_ANGLE));
        JSON k_umap(right);
        aux.push_back(k_umap);
    }

    all["tracks"] = aux;

    std::unordered_map<std::string, std::string> oils;
    std::unordered_map<std::string, std::string> muds;
    std::unordered_map<std::string, std::string> boulders;

    for (auto &element : track.get_static_elements()) {
        int t = element->get_entity_type();
        b2Vec2 a = element->get_position();
        switch (t) {
            case 3:
                oils.emplace("x", std::to_string(a.x));
                oils.emplace("y", std::to_string(a.y));
                break;
            case 2:
                muds.emplace("x", std::to_string(a.x));
                muds.emplace("y", std::to_string(a.y));
                break;
            case 4:
                boulders.emplace("x", std::to_string(a.x));
                boulders.emplace("y", std::to_string(a.y));
                break;
        }
    }
    aux_elements["oils"].push_back(JSON(oils));
    aux_elements["muds"].push_back(JSON(muds));
    aux_elements["boulders"].push_back(JSON(boulders));
    all["elements"] = aux_elements;

    return all;
}
