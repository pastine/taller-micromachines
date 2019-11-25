#include "server/Mud.h"

Mud::Mud(b2World &world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    m_body = world.CreateBody(&bodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = 0.5;
    b2FixtureDef fixture;
    fixture.shape = &circleShape;
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.isSensor = true;
    m_body->CreateFixture(&fixture);
    m_body->SetUserData(this);
}

void Mud::start_contact() {
}

void Mud::end_contact() {
}

int Mud::get_entity_type() {
    return MUD;
}
