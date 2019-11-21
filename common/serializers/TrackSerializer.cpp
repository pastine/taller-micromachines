#include <common/json.h>
#include <unordered_map>
#include <server/Oil.h>
#include "common/TrackSerializer.h"
#include "common/Constants.h"
#include "common/CommunicationConstants.h"

JSON TrackSerializer::serialize_to_json(
				std::unordered_map<std::string, std::vector<b2Vec2>>& track) {
    JSON all;
    JSON aux;
    JSON aux_elements;
    for (float i = FIRST_GROUND_TILE_X; i < 31.05f; i += W) {
        std::unordered_map<std::string, float> ground;
        ground.emplace(J_X, i);
        ground.emplace(J_Y, FIRST_GROUND_TILE_Y);
        ground.emplace(J_ANGLE, FIRST_GROUND_TILE_ANGLE);
        JSON j_umap(ground);
        aux.push_back(j_umap);
        std::unordered_map<std::string, float> ceiling;
        ceiling.emplace(J_X, i);
        ceiling.emplace(J_Y, FIRST_CEILING_TILE_Y);
        ceiling.emplace(J_ANGLE, FIRST_CEILING_TILE_ANGLE);
        JSON k_umap(ceiling);
        aux.push_back(k_umap);
    }

    for (float i = FIRST_LEFT_TILE_Y; i < 69.0f; i += W) {
        std::unordered_map<std::string, float> left;
        left.emplace(J_X, FIRST_LEFT_TILE_X);
        left.emplace(J_Y, i);
        left.emplace(J_ANGLE, FIRST_LEFT_TILE_ANGLE);
        JSON j_umap(left);
        aux.push_back(j_umap);
        std::unordered_map<std::string, float> right;
        right.emplace(J_X, FIRST_RIGHT_TILE_X);
        right.emplace(J_Y, i);
        right.emplace(J_ANGLE, FIRST_RIGHT_TILE_ANGLE);
        JSON k_umap(right);
        aux.push_back(k_umap);
    }

    all["tracks"] = aux;

    JSON oils, muds, boulders;

    auto aux_oils = track[J_OILS];
    auto aux_muds = track[J_MUD];
    auto aux_boulder = track[J_BOULDERS];

    for (size_t i = 0; i < aux_oils.size(); i++) {
    	std::unordered_map<std::string, float> oil;
    	oil.emplace(J_X, aux_oils[i].x);
    	oil.emplace(J_Y, aux_oils[i].y);
    	oils.push_back(JSON(oil));
			std::unordered_map<std::string, float> mud;
			mud.emplace(J_X, aux_muds[i].x);
			mud.emplace(J_Y, aux_muds[i].y);
			muds.push_back(JSON(mud));
			std::unordered_map<std::string, float> boulder;
			boulder.emplace(J_X, aux_boulder[i].x);
			boulder.emplace(J_Y, aux_boulder[i].y);
			boulders.push_back(JSON(boulder));
    }

    aux_elements[J_OILS]= oils;
    aux_elements[J_MUDS] = muds;
    aux_elements[J_BOULDERS] = boulders;
    all["elements"] = aux_elements;
    return std::move(all);
}
