#include "server/Boulder.h"
#include "common/Constants.h"

Boulder::Boulder(b2World &world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    m_body = world.CreateBody(&bodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = 0.3;
    b2FixtureDef fixture;
    fixture.shape = &circleShape;
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.isSensor = false;
    m_body->CreateFixture(&fixture);
    m_body->SetUserData(this);
}

void Boulder::start_contact() {
}

void Boulder::end_contact() {
}

int Boulder::get_entity_type() {
    return STONE;
}

