#include <common/json.h>
#include <unordered_map>
#include "common/TrackSerializer.h"
#include "common/Constants.h"

	std::string TrackSerializer::serialize(Track track) {
	JSON all;
	JSON aux;
	for (float i = FIRST_GROUND_TILE_X; i < 31.05; i+= W) {
		std::unordered_map<std::string, std::string> ground;
		ground.emplace(X, std::to_string(i));
		ground.emplace(Y, std::to_string(FIRST_GROUND_TILE_Y));
		ground.emplace(ANGLE, std::to_string(FIRST_GROUND_TILE_ANGLE));
		JSON j_umap(ground);
		aux.push_back(j_umap);
		std::unordered_map<std::string, std::string> ceiling;
		ceiling.emplace(X, std::to_string(i));
		ceiling.emplace(Y, std::to_string(FIRST_CEILING_TILE_Y));
		ceiling.emplace(ANGLE, std::to_string(FIRST_CEILING_TILE_ANGLE));
		JSON k_umap(ceiling);
		aux.push_back(k_umap);
	}

	for (float i = FIRST_LEFT_TILE_Y; i < 69; i += W) {
		std::unordered_map<std::string, std::string> left;
		left.emplace(X, std::to_string(FIRST_LEFT_TILE_X));
		left.emplace(Y, std::to_string(i));
		left.emplace(ANGLE, std::to_string(FIRST_LEFT_TILE_ANGLE));
		JSON j_umap(left);
		aux.push_back(j_umap);
		std::unordered_map<std::string, std::string> right;
		right.emplace(X, std::to_string(FIRST_RIGHT_TILE_X));
		right.emplace(Y, std::to_string(i));
		right.emplace(ANGLE, std::to_string(FIRST_RIGHT_TILE_ANGLE));
		JSON k_umap(right);
		aux.push_back(k_umap);
	}

	all["tracks"] = aux;
	return all.dump();
}
