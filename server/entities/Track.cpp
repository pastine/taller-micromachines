#include <server/Oil.h>
#include <server/Mud.h>
#include <server/Boulder.h>
#include <common/CommunicationConstants.h>
#include "server/Track.h"
#include "Box2D/Box2D.h"

Track::Track(b2World &world) {
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position.Set(0, 0);
    m_body = world.CreateBody(&def);
    b2PolygonShape walls;
    b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &walls;

    for (float i = FIRST_GROUND_TILE_X; i < 31.05; i += (W - 1)) {
        walls.SetAsBox(W / 2, H / 2, b2Vec2(i, FIRST_GROUND_TILE_Y), 0);//ground
        m_body->CreateFixture(&fixture);
    }
    for (float i = FIRST_CEILING_TILE_X; i < 31.05; i += (W - 1)) {
        walls.SetAsBox(W / 2, H / 2, b2Vec2(i, FIRST_CEILING_TILE_Y), 0);//ceiling
        m_body->CreateFixture(&fixture);
    }
    for (float i = FIRST_LEFT_TILE_Y; i < 69; i += (W - 1)) {
        walls.SetAsBox(H / 2, W / 2, b2Vec2(FIRST_LEFT_TILE_X, i), 0);//left wall
        m_body->CreateFixture(&fixture);
    }
    for (float i = FIRST_RIGHT_TILE_Y; i < 69; i += (W - 1)) {
        walls.SetAsBox(H / 2, W / 2, b2Vec2(FIRST_RIGHT_TILE_X, i), 0);//right wall
        m_body->CreateFixture(&fixture);
    }
    fixture.isSensor = true;
    int32 count = 3;

    //down right edge
    b2Vec2 vertices1[3];
    vertices1[0].Set(34.5f, 2.75f);
    vertices1[1].Set(34.5f, -2.75f);
    vertices1[2].Set(40.0f, 2.75f);
    b2PolygonShape edge1;
    edge1.Set(vertices1, count);
    b2FixtureDef fixture_edge1;
    fixture_edge1.shape = &edge1;
    fixture_edge1.isSensor = true;
    m_body->CreateFixture(&fixture_edge1);

    //down left edge
    b2Vec2 vertices2[3];
    vertices2[0].Set(-34.5f, 2.75f);
    vertices2[1].Set(-34.5f, -2.75f);
    vertices2[2].Set(-40.0f, 2.75f);
    b2PolygonShape edge2;
    edge2.Set(vertices2, count);
    b2FixtureDef fixture_edge2;
    fixture_edge2.shape = &edge2;
    fixture_edge2.isSensor = true;
    m_body->CreateFixture(&fixture_edge2);

    //top left edge
    b2Vec2 vertices3[3];
    vertices3[0].Set(-34.5f, 71.75f);
    vertices3[1].Set(-34.5f, 77.25f);
    vertices3[2].Set(-40.0f, 71.75f);
    b2PolygonShape edge3;
    edge3.Set(vertices3, count);
    b2FixtureDef fixture_edge3;
    fixture_edge3.shape = &edge3;
    fixture_edge3.isSensor = true;
    m_body->CreateFixture(&fixture_edge3);

    //top right edge
    b2Vec2 vertices4[3];
    vertices4[0].Set(34.5f, 71.75f);
    vertices4[1].Set(34.5f, 77.25f);
    vertices4[2].Set(40.0f, 71.75f);
    b2PolygonShape edge4;
    edge4.Set(vertices4, count);
    b2FixtureDef fixture_edge4;
    fixture_edge4.shape = &edge4;
    fixture_edge4.isSensor = true;
    m_body->CreateFixture(&fixture_edge4);

    m_body->SetUserData(this);

    for (int i = 0; i < 5; i++) {
        std::vector<float> oil_pos = Element::get_random_pos();
        Oil *o = new Oil(world, oil_pos[0], oil_pos[1]);
        static_elements.emplace_back(o);

        std::vector<float> mud_pos = Element::get_random_pos();
        Mud *m = new Mud(world, mud_pos[0], mud_pos[1]);
        static_elements.emplace_back(m);

        std::vector<float> boulder_pos = Element::get_random_pos();
        Boulder *s = new Boulder(world, boulder_pos[0], boulder_pos[1]);
        static_elements.emplace_back(s);

				std::vector<float> fav = Element::get_random_pos();
				Element* element = Element::get_element(world);
				elements.emplace_back(element);//TODO bien solo 5?
    }
}

int Track::get_entity_type() {
    return TRACK;
}

b2Vec2 Track::get_position() {
    return m_body->GetPosition();
}

std::unordered_map<std::string, std::string> Track::get_elements_state() {
//    std::unordered_map<std::string, std::string> user;
//    user.emplace("mud", car->get_mud_state());
//    user.emplace("lives", car->get_lives());
//    return user;
    return {};
}

std::vector<Element *> Track::get_static_elements() {
    return static_elements;
}

void Track::delete_elements() {
    for (auto &e : static_elements)
        delete (e);
}

void Track::add_elements(State &state) {
    state.append(J_ELEMENTS, get_elements_state());
}
