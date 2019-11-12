#include <iostream>
#include "server/Car.h"
#define MAX 100
#define FORCE 800
#define DEGTORAD 0.0174532925199432957f

b2Vec2 get_forward_normal(float angle) {
	float correction = 1;
	if (angle > 0) {correction = -1;}
	angle = abs(angle);
	angle *= DEGTORAD;
	b2Vec2 normal;
	normal.x = sin(angle) * correction;
	normal.y = cos(angle);
	return normal;
}

Car::Car(b2World &world, unsigned long i) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(4*i, 0.0f);
  car = world.CreateBody(&bodyDef);
  b2Vec2 vertices[4];
  vertices[0].Set(0.0f, 0.0f);
  vertices[1].Set(1.0f, 0.0f);
  vertices[2].Set(1.0f, 3.0f);
  vertices[3].Set(0.0f, 3.0f);
  int32 count = 4;
  b2PolygonShape dynamicBox;
  dynamicBox.Set(vertices, count);
  dynamicBox.SetAsBox(1.0f, 1.5f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  car->CreateFixture(&fixtureDef);
  max_speed = MAX;
  min_speed = -MAX;
  car->SetUserData(this);
  track = true;
  lives = 3;
  visibility = true;
}

b2Vec2 Car::get_position() {
  return car->GetPosition();
}

float32 Car::get_angle() {
  float32 angle = car->GetAngle();
  while (angle < -180) {angle += 360;}
  while (angle > 180) {angle -= 360;}
  return angle;
}

void Car::turn_left() {
    car->ApplyTorque(FORCE,true);
    this->move_forward();
    car->SetAngularDamping(1.5);
}

void Car::turn_right() {
    car->ApplyTorque(- FORCE,true);
    this->move_forward();
    car->SetAngularDamping(1.5);
}

void Car::move_forward() {
  float angle = this->get_angle();
  b2Vec2 normal = get_forward_normal(angle);
  float force = 0;
  float currentSpeed = b2Dot(car->GetLinearVelocity(), normal);
  if (currentSpeed < max_speed) {
    force = FORCE;
  }
  car->ApplyForce(force * normal, car->GetPosition(), true);
  car->SetLinearDamping(1.5);
}

void Car::stop() {
	float angle = this->get_angle();
	b2Vec2 normal = get_forward_normal(angle);
  float force = 0;
  float currentSpeed = b2Dot(car->GetLinearVelocity(), normal);
  if (currentSpeed > min_speed) {
    force = - FORCE;
  }
  car->ApplyForce(force * normal, car->GetPosition(), true);
  car->SetLinearDamping(1.5);
}

void Car::start_contact(int id) {
	switch (id) {
		case TRACK : this->on_track(); return;
		case CAR : this->contact_car(); return;
		case MUD : this->contact_mud(); return;
		case OIL : this->contact_oil(); return;
		case STONE: this->contact_stone(); return;
		case HEALTH: this->contact_health(); return;
		case BOOST: this->contact_boost(); return;
		default: return;
	}
}

void Car::end_contact(int id) {
	if(id == 0) {
		this->off_track();
	}
	return;
}

void Car::on_track() {
	std::cout<<"estoy en la pista\n";
  track = true;
}

void Car::off_track() {
	std::cout<<"NO estoy en la pista\n";
  track = false;
}

void Car::contact_car() {
	lives--;
}

void Car::contact_mud() {
	visibility = false;
}

void Car::contact_oil() {
	float friction = car->GetFixtureList()->GetFriction();
	friction -= 0.3;
	car->GetFixtureList()->SetFriction(friction);
}

void Car::contact_stone() {
	this->stop();
	lives--;
}

void Car::contact_health() {
	if(lives < 3) {lives++;}
}

void Car::contact_boost() {
	float angle = this->get_angle();
	b2Vec2 normal = get_forward_normal(angle);
	float force = 1000;
	car->ApplyForce(force * normal, car->GetPosition(), true);
	car->SetLinearDamping(1.0);
}


int Car::get_entity_type() {
	return CAR;
}


void Car::surface_effect() {
	if (!track) {this->stop();}
}

std::string Car::get_lives() {
	return std::move(std::to_string(lives));
}

std::string Car::get_mud_state() {
	if (!visibility) {
		visibility = true;
		return "true";
	}
	return "false";
}

Car::~Car() {
}

