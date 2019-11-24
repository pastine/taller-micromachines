#include <common/json.h>
#include <unordered_map>
#include "common/TrackSerializer.h"
#include "common/CommunicationConstants.h"

JSON TrackSerializer::serialize_to_json(TrackData& track) {
		auto track_roads = track.get_track();
		auto track_elements = track.get_elements();
	
    JSON all;
    JSON aux_elements;
    
    all["tracks"] = track_roads["straight"];
    all["curved"] = track_roads["curved_center"];

    JSON oils, muds, boulders;
    auto aux_oils = track_elements[J_OILS];
    auto aux_muds = track_elements[J_MUDS];
    auto aux_boulder = track_elements[J_BOULDERS];

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
