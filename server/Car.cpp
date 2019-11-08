#include <iostream>
#include "server/Car.h"
#define MAX 100
#define SPEED 20
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Car::Car(b2World &world, unsigned long i) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(6.0f * i , 0.0f);
  car = world.CreateBody(&bodyDef);
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
  car->CreateFixture(&fixtureDef);
  max_speed = MAX;
  min_speed = -MAX;
  car->SetUserData(this);
  track = true;
}

b2Vec2 Car::get_position() {
  //std::cout<<"En x: "<<car->GetPosition().x;
  //std::cout<<", En y:"<<car->GetPosition().y;
  return car->GetPosition();
}

float32 Car::get_angle() {
  float32 angle = car->GetAngle();
  while (angle < -180) {angle += 360;}
  while (angle > 180) {angle -= 360;}
  return angle;
}

void Car::set_linear_velocity(b2Vec2& v) {
  car->SetLinearVelocity(v);
}

void Car::set_angular_velocity(float32 omega) {
  car->SetAngularVelocity(omega);
}

b2Vec2 Car::get_lateral_velocity() {
  b2Vec2 currentRightNormal = car->GetWorldVector(b2Vec2(1,0));
  return b2Dot( currentRightNormal, car->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 Car::get_forward_velocity() {
  b2Vec2 currentRightNormal = car->GetWorldVector(b2Vec2(0,1));
  return b2Dot( currentRightNormal, car->GetLinearVelocity() ) * currentRightNormal;
}

void Car::updateFriction() {
  b2Vec2 impulse = car->GetMass() * -get_lateral_velocity();
  car->ApplyLinearImpulse(impulse,car->GetWorldCenter(),true);
  car->ApplyAngularImpulse(0.1f * car->GetInertia() * -car->GetAngularVelocity(), true);
  b2Vec2 fn = get_forward_velocity();
  float cfs = fn.Normalize();
  float dfm = -2 * cfs;
  car->ApplyForce(dfm * fn, car->GetWorldCenter(), true);
  b2Vec2 i = car->GetMass() * -get_lateral_velocity();
  if (i.Length() > 3) i *= 3 / i.Length();
  car->ApplyLinearImpulse(i, car->GetWorldCenter(),true);
}

void Car::turn_left() {
  updateFriction();
  car->ApplyTorque(50,true);
}

void Car::turn_right() {
  updateFriction();
  car->ApplyTorque(-50,true);
  /*float32 angle = get_angle();
  b2Vec2 correction(cos(angle) + 1.5f * sin(angle), - sin(angle) + 1.5f * cos(angle));
  b2Vec2 force = car->GetPosition() + correction;
  car->ApplyForce(b2Vec2(-10 * sin(angle), -10 * cos(angle)), force, true);
  car->SetLinearDamping(0);*/
}

void Car::move_forward() {
  b2Vec2 forward_normal = car->GetWorldVector(b2Vec2(0,1));
  float currentSpeed = b2Dot(this->get_forward_velocity(), forward_normal);
  float force = 0;
  if (currentSpeed < max_speed) {
    force = 100;
  }
  car->ApplyForce(force * forward_normal, car->GetPosition(), true);
  car->SetLinearDamping(0);
}

void Car::stop() {
  b2Vec2 forward_normal = car->GetWorldVector(b2Vec2(0,1));
  float currentSpeed = b2Dot(this->get_forward_velocity(), forward_normal);
  float force = 0;
  if (currentSpeed > min_speed) {
    force = -100;
  }
  car->ApplyForce(force * forward_normal, car->GetPosition(), true);
  car->SetLinearDamping(0);
}

void Car::start_contact() {
  this->stop();
}

void Car::end_contact() {
}

void Car::on_track() {
  track = true;
}

void Car::off_track() {
  track = false;
}

Car::~Car() {
}

void Car::surface_effect() {
  if (!track) {this->stop();}
}
