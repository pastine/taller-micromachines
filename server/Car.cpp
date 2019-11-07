#include <iostream>
#include "server/Car.h"
#define MAX 100
#define SPEED 20
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

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
  listener = ContactListener();
  contacts = 0;
  m_body->SetUserData(this);
  track = true;
}

b2Vec2 Car::get_position() {
  //std::cout<<"En x: "<<m_body->GetPosition().x;
  //std::cout<<", En y:"<<m_body->GetPosition().y;
  return m_body->GetPosition();
}

float32 Car::get_angle() {
  float32 angle = m_body->GetAngle();
  while (angle < -180) {angle += 360;}
  while (angle > 180) {angle -= 360;}
  return angle;
}

bool Car::is_colliding() {
  return contacts > 0;
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

void Car::turn_right() {
  float32 angle = get_angle();
  b2Vec2 correction(cos(angle) + 1.5f * sin(angle), - sin(angle) + 1.5f * cos(angle));
  b2Vec2 force = m_body->GetPosition() + correction;
  m_body->ApplyForce(b2Vec2(-10 * sin(angle), -10 * cos(angle)), force, true);
  m_body->SetLinearDamping(0);
}

void Car::move_forward() {
  float32 angle = get_angle();
  b2Vec2 velocity = m_body->GetLinearVelocity();
  if (velocity.y < max_speed) {
    velocity.y += SPEED;
  } else {
    return;
  }
  m_body->ApplyForce(b2Vec2(30 * sin(angle), 30 * cos(angle)), m_body->GetPosition(), true);
  m_body->SetLinearDamping(0);
}


void Car::stop() {
  b2Vec2 velocity = m_body->GetLinearVelocity();
  if (velocity.y > min_speed) {
    velocity.y += SPEED;
  } else {
    return;
  }
  m_body->ApplyForce(b2Vec2(0, velocity.y), m_body->GetPosition(), true);
  m_body->SetLinearDamping(0);
}

void Car::start_contact() {
  contacts++;
}

void Car::end_contact() {
  contacts--;
}

void Car::on_track() {
  std::cout<<"en pista\n";
  track = true;
}

void Car::off_track() {
  std::cout<<"fuera pista\n";
  track = false;
}

Car::~Car() {
}
