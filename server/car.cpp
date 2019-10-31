#include "server/car.h"
#define MAX 100

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
  max_speed = MAX;
  min_speed = -MAX;
}

b2Vec2 Car::get_position() {
  return m_body->GetPosition();
}

float32 Car::get_angle() {
  return m_body->GetAngle();
}

void Car::set_linear_velocity(b2Vec2& v) {
  m_body->SetLinearVelocity(v);
}

void Car::set_angular_velocity(float32 omega) {
  m_body->SetAngularVelocity(omega);
}

b2Vec2 Car::get_lateral_velocity() {
  b2Vec2 currentRightNormal = m_body->GetWorldVector(b2Vec2(1,0));
  return b2Dot( currentRightNormal, m_body->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 Car::get_forward_velocity() {
  b2Vec2 currentRightNormal = m_body->GetWorldVector(b2Vec2(0,1));
  return b2Dot( currentRightNormal, m_body->GetLinearVelocity() ) * currentRightNormal;
}

void Car::updateFriction() {
  b2Vec2 impulse = m_body->GetMass() * -get_lateral_velocity();
  m_body->ApplyLinearImpulse(impulse, m_body->GetWorldCenter(), false);
}

void Car::turn(float torque) {
  m_body->ApplyTorque(torque, true);
}

void Car::move_forward() {
  b2Vec2 normal = m_body->GetWorldVector(b2Vec2(0,1) );
  float speed = b2Dot(this->get_forward_velocity(), normal);

  float force = 0;
  if (speed < max_speed) {
    force = MAX;
  } else {
    return;
  }
  m_body->ApplyForce(force * normal, m_body->GetWorldCenter(),true);
}

void Car::stop() {
  b2Vec2 normal = m_body->GetWorldVector(b2Vec2(0, 1));
  float speed = b2Dot(this->get_forward_velocity(), normal);

  float force = 0;
  if (speed > min_speed) {
    force = -MAX;
  } else {
    return;
  }
  m_body->ApplyForce(force * normal, m_body->GetWorldCenter(), true);
}

Car::~Car() {
  m_body->GetWorld()->DestroyBody(m_body);
}
