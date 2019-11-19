#include "server/Boost.h"
#include "common/Constants.h"

Boost::Boost(b2World &world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    m_body = world.CreateBody(&bodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0); //position, relative to body position
    circleShape.m_radius = 0.5; //TODO define dimension
    b2FixtureDef fixture;
    fixture.shape = &circleShape; //this is a pointer to the shape above
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.isSensor = true;
    m_body->CreateFixture(&fixture);
    m_body->SetUserData(this);
}

void Boost::start_contact() {
    //nothing for me
}

void Boost::end_contact() {
    this->destroy();
}

void Boost::destroy() {
    m_body->GetWorld()->DestroyBody(m_body);
}

int Boost::get_entity_type() {
    return BOOST;
}



