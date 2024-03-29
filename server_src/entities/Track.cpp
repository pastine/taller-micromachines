#include <server/Oil.h>
#include <server/Mud.h>
#include <server/Boulder.h>
#include <server/Boost.h>
#include <server/Health.h>
#include <common/CommunicationConstants.h>
#include <random>
#include "server/Track.h"
#include "Box2D/Box2D.h"

std::vector<std::vector<float>> fill_pos(JSON pos) {
    std::vector<std::vector<float>> positions;
    for (auto &element : pos) {
        std::vector<float> aux = {element[J_X], element[J_Y]};
        positions.emplace_back(aux);
    }
    std::default_random_engine rng(time(NULL));
    std::shuffle(positions.begin(), positions.end(), rng);
    return std::move(positions);
}

Track::Track(b2World *world, char *file) : skeleton(TrackStructure(file)),
                                           world(world) {
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position.Set(0, 0);
    m_body = world->CreateBody(&def);
    b2PolygonShape walls;
    b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &walls;
    fixture.isSensor = true;
    JSON track = skeleton.get_track();
    JSON straight = track[J_STRAIGHT];
    JSON curved = track[J_CURVED];

    positions = fill_pos(straight);

    for (JSON::iterator it = straight.begin(); it != straight.end(); ++it) {
        JSON aux = *it;
        float x = aux[J_X];
        float y = aux[J_Y];
        walls.SetAsBox(W / 2, W / 2, b2Vec2(x, y), 0);
        m_body->CreateFixture(&fixture);
    }

    int count = 3; //triangle
    for (JSON::iterator it = curved.begin(); it != curved.end(); ++it) {
        JSON aux = *it;
        float x0 = aux[J_X0], y0 = aux[J_Y0];
        float x1 = aux[J_X1], y1 = aux[J_Y1];
        float x2 = aux[J_X2], y2 = aux[J_Y2];
        b2Vec2 vertex[3];
        vertex[0].Set(x0, y0);
        vertex[1].Set(x1, y1);
        vertex[2].Set(x2, y2);
        b2PolygonShape edge;
        edge.Set(vertex, count);
        b2FixtureDef fixture_edge;
        fixture_edge.shape = &edge;
        fixture_edge.isSensor = true;
        m_body->CreateFixture(&fixture_edge);
    }

    m_body->SetUserData(this);

    for (int i = 0; i < 3; i++) {
        std::vector<float> oil_pos = get_random_pos();
        Oil *o = new Oil(*world, oil_pos[0], oil_pos[1]);
        static_elements.emplace_back(o);

        std::vector<float> mud_pos = get_random_pos();
        Mud *m = new Mud(*world, mud_pos[0], mud_pos[1]);
        static_elements.emplace_back(m);

        std::vector<float> boulder_pos = get_random_pos();
        Boulder *s = new Boulder(*world, boulder_pos[0], boulder_pos[1]);
        static_elements.emplace_back(s);

        std::vector<float> health_pos = get_random_pos();
        Health *h = new Health(*world, health_pos[0], health_pos[1]);
        elements.emplace_back(h);

        std::vector<float> boost_pos = get_random_pos();
        Boost *boost = new Boost(*world, boost_pos[0], boost_pos[1]);
        elements.emplace_back(boost);
    }
}

int Track::get_entity_type() {
    return TRACK;
}

JSON Track::get_elements_state() {
    JSON boost, health;
    to_remove.clear();
    std::vector<Consumable *> new_elements;
    for (auto &e : elements) {
        int id = e->get_entity_type();
        bool consumed = e->was_consumed();
        b2Vec2 pos = e->get_position();
        if (consumed) {
            std::vector<float> aux;
            aux.emplace_back(pos.x);
            aux.emplace_back(pos.y);
            std::vector<float> new_pos = get_random_pos();
            if (id == BOOST) {
                Boost *new_boost = new Boost(*world, new_pos[0], new_pos[1]);
                pos = new_boost->get_position();
                new_elements.emplace_back(new_boost);
                to_remove.emplace_back(e);
            } else {
                Health *new_health = new Health(*world, new_pos[0], new_pos[1]);
                pos = new_health->get_position();
                new_elements.emplace_back(new_health);
                to_remove.emplace_back(e);
            }
            positions.push_back(aux);
            std::default_random_engine rng(time(NULL));
            std::shuffle(positions.begin(), positions.end(), rng);
        } else {
            auto *a = e;
            new_elements.emplace_back(a);
        }
        std::unordered_map<std::string, float> aux;
        aux.emplace(J_X, pos.x);
        aux.emplace(J_Y, pos.y);
        if (id == BOOST) {
            boost.push_back(JSON(aux));
        } else {
            health.push_back(JSON(aux));
        }
    }
    elements.clear();
    elements = new_elements;
    JSON elemen;
    elemen[J_BOOST] = boost;
    elemen[J_HEALTH] = health;
    return elemen;
}

std::vector<Consumable *> Track::get_removable_elements() {
    auto aux = to_remove;
    to_remove.clear();
    return aux;
}

TrackData Track::get_static_data() {
    std::vector<b2Vec2> mud;
    std::vector<b2Vec2> oil;
    std::vector<b2Vec2> boulder;
    for (auto &e : static_elements) {
        int id = e->get_entity_type();
        switch (id) {
            case MUD:
                mud.emplace_back(e->get_position());
                break;
            case OIL:
                oil.emplace_back(e->get_position());
                break;
            case STONE:
                boulder.emplace_back(e->get_position());
                break;
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
    auto pos = positions.back();
    positions.pop_back();
    return pos;
}

JSON Track::get_straight_points() {
    auto aux = skeleton.get_track()[J_CURVED_CENTER];
    return aux;
}

Track::~Track() {
    for (auto &e: static_elements) {
        delete (e);
    }
    for (auto &e: elements) {
        delete (e);
    }
    for (auto &e: to_remove) {
        delete (e);
    }
}


