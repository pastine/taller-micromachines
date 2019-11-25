#include "server/Boost.h"
#include "common/Constants.h"

Boost::Boost(b2World &world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    m_body = world.CreateBody(&bodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = 0.5;
    b2FixtureDef fixture_def;
    fixture_def.shape = &circleShape;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;
    fixture_def.isSensor = true;
    fixture = m_body->CreateFixture(&fixture_def);
    m_body->SetUserData(this);
}

void Boost::start_contact() {
}

void Boost::end_contact() {
	consumed = true;
}

int Boost::get_entity_type() {
    return BOOST;
}

Boost::~Boost() {
	m_body->DestroyFixture(fixture);
	fixture = nullptr;
	m_body->GetWorld()->DestroyBody(m_body);
	m_body = nullptr;
}




