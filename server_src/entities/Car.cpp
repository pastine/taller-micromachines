#include <iostream>
#include <random>
#include "server/Car.h"

#define MAX 30.0f
#define MIN_TURN_SPEED 1.0f
#define TORQUE 1800.0f
#define FORCE 40.0f
#define DEGTORAD 0.0174532925199432957f

b2Vec2 get_forward_normal(float angle) {
    float correction = 1;
    if (angle > 0) { correction = -1; }
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
    bodyDef.position.Set(7 * i + START_POINT_X, START_POINT_Y);
    m_body = world.CreateBody(&bodyDef);
    b2Vec2 vertices[4];
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(0.29f * CAR_RESIZE_FACTOR, 0.0f);
    vertices[2].Set(0.29f * CAR_RESIZE_FACTOR, 0.29f * CAR_RESIZE_FACTOR);
    vertices[3].Set(0.0f, 0.29f * CAR_RESIZE_FACTOR);
    int32 count = 4;
    b2PolygonShape dynamicBox;
    dynamicBox.Set(vertices, count);
    dynamicBox.SetAsBox(0.145f * CAR_RESIZE_FACTOR, 0.145f * CAR_RESIZE_FACTOR);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 40.0f;
    fixtureDef.friction = 11.0f;
    fixtureDef.restitution = 0.3f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
    max_speed = MAX;
    min_speed = -MAX;
    min_turn_speed = MIN_TURN_SPEED;
    track = true;
    lives = new int(3);
    visibility = false;
    crash = false;
}

b2Vec2 Car::get_position() {
    return m_body->GetPosition();
}

float32 Car::get_angle() {
    float32 angle = m_body->GetAngle();
    while (angle < -180) { angle += 360; }
    while (angle > 180) { angle -= 360; }
    return angle;
}

void Car::turn(bool turn_left) {
    float currentSpeed = get_speed();
    if (currentSpeed > -min_turn_speed && currentSpeed < min_turn_speed) return;
    if (turn_left)
        m_body->ApplyTorque(TORQUE, true);
    else
        m_body->ApplyTorque(-TORQUE, true);
    m_body->SetAngularDamping(3);
    int angle = std::abs(this->get_angle());
    if (angle <= 3 || (angle >= 87 && angle <= 93) || (angle >= 177))
        m_body->SetAngularDamping(3);
}

void Car::move_straight(bool move_forward) {
    float angle = this->get_angle();
    float force = 0;
    b2Vec2 normal = get_forward_normal(angle);
    float currentSpeed = get_speed();
    if (move_forward && currentSpeed < max_speed)
        force = FORCE;
    else if (!move_forward && currentSpeed > min_speed)
        force = -FORCE / 2;
    m_body->ApplyLinearImpulse(force * normal, m_body->GetPosition(), true);
    m_body->SetLinearDamping(3);
}

void Car::start_contact(int id) {
    switch (id) {
        case TRACK :
            this->on_track();
            return;
        case CAR :
            this->contact_car();
            return;
        case MUD :
            this->contact_mud();
            return;
        case OIL :
            this->contact_oil();
            return;
        case STONE:
            this->contact_stone();
            return;
        case HEALTH:
            this->contact_health();
            return;
        case BOOST:
            this->contact_boost();
            return;
        case LIMIT:
            this->contact_limit();
            return;
        default:
            return;
    }
}

void Car::end_contact(int id) {
    if (id == TRACK) {
        this->off_track();
    }
}

void Car::on_track() {
    float friction = m_body->GetFixtureList()->GetFriction();
    friction += 15;
    m_body->GetFixtureList()->SetFriction(friction);
    track = true;
}

void Car::off_track() {
    float friction = m_body->GetFixtureList()->GetFriction();
    if ((friction - 15.0f) <= 0) return;
    friction -= 15;
    m_body->GetFixtureList()->SetFriction(friction);
    track = false;
}

void Car::contact_car() {
    crash_car = true;
    (*lives) -= 1;
    if ((*lives) == 0) {
        back_to_track();
        (*lives) += 3;
    }
}

void Car::contact_mud() {
    slip = true;
    visibility = true;
}

void Car::contact_oil() {
    slip = true;
    float friction = m_body->GetFixtureList()->GetFriction();
    if ((friction - 8.0f) <= 0) return;
    friction -= 8.0f;
    m_body->GetFixtureList()->SetFriction(friction);
}

void Car::contact_stone() {
    crash = true;
    if ((*lives) == 0) {
        back_to_track();
        (*lives) += 3;
    }
    (*lives) -= 1;
    if ((*lives) == 0) { (*lives) += 3; }
}

void Car::contact_health() {
    if ((*lives) < 3) {
        powerup = true;
        (*lives) += 1;
    }
}

void Car::contact_boost() {
    powerup = true;
    float angle = this->get_angle();
    b2Vec2 normal = get_forward_normal(angle);
    float force = 20000;
    m_body->ApplyForce(force * normal, m_body->GetPosition(), true);
    m_body->SetLinearDamping(1.0);
}


int Car::get_entity_type() {
    return CAR;
}

int Car::get_lives() {
    return *lives;
}

bool Car::get_crash_state() {
    if (crash) {
        crash = false;
        return true;
    }
    return false;
}

bool Car::get_crash_car_state() {
    if (crash_car) {
        crash_car = false;
        return true;
    }
    return false;
}

bool Car::get_powerup_state() {
    if (powerup) {
        powerup = false;
        return true;
    }
    return false;
}

bool Car::get_slip_state() {
    if (slip) {
        slip = false;
        return true;
    }
    return false;
}

bool Car::get_mud_state() {
    if (visibility) {
        visibility = false;
        return true;
    }
    return false;
}

float Car::get_speed() {
    float angle = this->get_angle();
    b2Vec2 normal = get_forward_normal(angle);
    return b2Dot(m_body->GetLinearVelocity(), normal);
}

void Car::back_to_track() {
    b2Vec2 pos = this->get_position();
    b2Vec2 force = {-pos.x * TORQUE, -pos.y * TORQUE};
    m_body->ApplyLinearImpulse(force, m_body->GetWorldCenter(), true);
}

void Car::contact_limit() {
    crash = true;
    if ((*lives) == 0) {
        back_to_track();
        (*lives) += 3;
    }
    (*lives) -= 1;
    if ((*lives) == 0) { (*lives) += 3; }
}

Car::~Car() {
    delete (lives);
}
