#include <server/Oil.h>
#include <server/Mud.h>
#include <server/Boulder.h>
#include <server/Boost.h>
#include <server/Health.h>
#include <common/CommunicationConstants.h>
#include <random>
#include "server/Track.h"
#include "Box2D/Box2D.h"

Track::Track(b2World &world, char* file) : skeleton(TrackStructure(file)) {
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position.Set(0, 0);
    m_body = world.CreateBody(&def);
    b2PolygonShape walls;
    b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &walls;
    JSON track = skeleton.get_track()["straight"];

    for (JSON::iterator it = track.begin(); it != track.end(); ++it) {
    	JSON aux = *it;
    	float x = aux["x"];
    	float y = aux["y"];
    	walls.SetAsBox(W/2, W/2, b2Vec2(x, y), 0);
    	m_body->CreateFixture(&fixture);
    }

    fixture.isSensor = true;
    //int32 count = 3;

    m_body->SetUserData(this);

    for (int i = 0; i < 3; i++) {
        std::vector<float> oil_pos = get_random_pos();
        Oil *o = new Oil(world, oil_pos[0], oil_pos[1]);
        static_elements.emplace_back(o);

        std::vector<float> mud_pos = get_random_pos();
        Mud *m = new Mud(world, mud_pos[0], mud_pos[1]);
        static_elements.emplace_back(m);

        std::vector<float> boulder_pos = get_random_pos();
        Boulder *s = new Boulder(world, boulder_pos[0], boulder_pos[1]);
        static_elements.emplace_back(s);

				std::vector<float> health_pos = get_random_pos();
				Health *h = new Health(world, health_pos[0], health_pos[1]);
				elements.emplace_back(h);

				std::vector<float> boost_pos = get_random_pos();
				Boost *boost = new Boost(world, boost_pos[0], boost_pos[1]);
				elements.emplace_back(boost);
    }
}

int Track::get_entity_type() {
    return TRACK;
}

b2Vec2 Track::get_position() {
    return m_body->GetPosition();
}

JSON Track::get_elements_state() {
	JSON boost;
	JSON health;
	for (auto &e : elements) {
		int id = e->get_entity_type();
		auto pos = e->get_position();
		std::unordered_map<std::string, float> aux;
		aux.emplace(J_X, pos.x);
		aux.emplace(J_Y, pos.y);
		JSON j_umap(aux);
		if (id  == BOOST) {
			boost.push_back(j_umap);
		} else {
			health.push_back(j_umap);
		}
	}
	JSON elemen;
	elemen["boost"] = boost;
	elemen["health"] = health;
	return elemen;
}

TrackData Track::get_static_data() {
	std::vector<b2Vec2> mud;
	std::vector<b2Vec2> oil;
	std::vector<b2Vec2> boulder;
	for (auto &e : static_elements) {
		int id = e->get_entity_type();
		switch (id) {
			case MUD: mud.emplace_back(e->get_position()); break;
			case OIL: oil.emplace_back(e->get_position()); break;
			case STONE: boulder.emplace_back(e->get_position()); break;
		}
	}
	std::unordered_map<std::string, std::vector<b2Vec2>> result;
	result.emplace(J_BOULDERS, boulder);
	result.emplace(J_OILS, oil);
	result.emplace(J_MUDS, mud);

	TrackData all(result, skeleton.get_track());

	return all;
}

std::vector<float> Track::get_random_pos() {
	JSON pos = skeleton.get_track()["straight"];
	auto top = pos.size();
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, top);
	int num = dist(mt);
	auto new_pos = pos[num];
	return std::vector<float>{new_pos["x"], new_pos["y"]};
}

Track::~Track() {
	for (auto &e : static_elements) {
		delete (e);
	}
	for (auto &a : elements) {
		delete (a);
	}
}
