#include <Box2D/Box2D.h>
#include "server/Mud.h"

Mud::Mud(b2World& world) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 0.0f); //TODO method that randomizes position
  m_body = world.CreateBody(&bodyDef);

  //Define shape
  b2CircleShape circleShape;
  circleShape.m_p.Set(0, 0); //position, relative to body position
  circleShape.m_radius = 1;

  b2FixtureDef fixture;
  fixture.shape = &circleShape; //this is a pointer to the shape above
  fixture.density = 1.0f;
  fixture.friction = 0.3f;
  m_body->CreateFixture(&fixture);

  contact = ContactListener();
  contacts = 0;
  m_body->SetUserData(this);
}

void Mud::start_contact() {
  contacts++;
}

void Mud::end_contact() {
  contacts--;
}
