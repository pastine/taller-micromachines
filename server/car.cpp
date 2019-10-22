#include "car.h"

Car::Car(b2World& world){
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 0.0f);
  m_body = world.CreateBody(&bodyDef);

  //Define shape
  b2Vec2 vertices[4];
  vertices[0].Set(0.0f, 0.0f);
  vertices[1].Set(1.0f, 0.0f);
  vertices[2].Set(1.0f, 3.0f);
  vertices[3].Set(0.0f, 3.0f);
  int32 count = 4;

  // Define another box shape for our dynamic body.
  b2PolygonShape dynamicBox;
  dynamicBox.Set(vertices, count);
  dynamicBox.SetAsBox(1.0f, 1.5f);

  // Define the dynamic body fixture, density, friction
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  // Add the shape to the body.
  m_body->CreateFixture(&fixtureDef);
}

b2Vec2 Car::get_position() {
  return m_body->GetPosition();
}

float32 Car::get_angle() {
  return m_body->GetAngle();
}

b2Vec2 Car::getLateralVelocity() {
  b2Vec2 currentRightNormal = m_body->GetWorldVector( b2Vec2(1,0) );
  return b2Dot( currentRightNormal, m_body->GetLinearVelocity() ) * currentRightNormal;
}

void Car::updateFriction() {
  b2Vec2 impulse = m_body->GetMass() * -getLateralVelocity();
  m_body->ApplyLinearImpulse( impulse, m_body->GetWorldCenter() );
}

Car::~Car() {
  m_body->GetWorld()->DestroyBody(m_body);
}