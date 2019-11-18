#include "server/Stone.h"
#include "common/Constants.h"

Stone::Stone(b2World& world, float x, float y) {
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

void Stone::start_contact() {
	//nothing for me
}

void Stone::end_contact() {
	this->destroy();
}

void Stone::destroy() {
	//m_body->GetWorld()->DestroyBody(m_body);
}

int Stone::get_entity_type() {
	return STONE;
}

b2Vec2 Stone::get_position() {
    return m_body->GetPosition();
}


