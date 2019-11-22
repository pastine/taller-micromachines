#include <common/json.h>
#include <unordered_map>
#include <server/Oil.h>
#include "common/TrackSerializer.h"
#include "common/Constants.h"
#include "common/CommunicationConstants.h"
#include "../../server/TrackStructure.h"

JSON TrackSerializer::serialize_to_json(
				std::unordered_map<std::string, std::vector<b2Vec2>>& track) {
    JSON all;
    JSON aux_elements;

		TrackStructure skeleton;
    all["tracks"] = skeleton.get_track()["straight"];

    JSON oils, muds, boulders;

    auto aux_oils = track[J_OILS];
    auto aux_muds = track[J_MUDS];
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
