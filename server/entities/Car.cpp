#include <iostream>
#include "common/Constants.h"
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
    //bodyDef.position.Set(10*i+STARTPOINT_X, 16*i+STARTPOINT_Y);
    bodyDef.position.Set(0, 0);
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
    max_speed = MAX;
    min_speed = -MAX;
    min_turn_speed = MIN_TURN_SPEED;
    m_body->SetUserData(this);
    track = true;
    lives = new int(3);
    visibility = true;
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
    if (id == 0) {
        this->off_track();
    }
}

void Car::on_track() {
    track = true;
    if (track) { std::cout << "on track----------\n"; }
}

void Car::off_track() {
    track = false;
    if (!track) { std::cout << "off track----------\n"; }
}

void Car::contact_car() {
    *lives -= 1;
}

void Car::contact_mud() {
    visibility = false;
}

void Car::contact_oil() {
    float friction = m_body->GetFixtureList()->GetFriction();
    friction -= 0.3f;
    m_body->GetFixtureList()->SetFriction(friction);
}

void Car::contact_stone() {
    this->move_straight(false);
    *lives -= 1;
}

void Car::contact_health() {
    if (*lives < 3) { *lives += 1; }
}

void Car::contact_boost() {
    float angle = this->get_angle();
    b2Vec2 normal = get_forward_normal(angle);
    float force = 1000;
    m_body->ApplyForce(force * normal, m_body->GetPosition(), true);
    m_body->SetLinearDamping(1.0);
}


int Car::get_entity_type() {
    return CAR;
}


void Car::surface_effect() {
    /*if (track) {
        std::cout<<"ontrack"<<"\n";
    }
    if (!track) {
        std::cout<<"offtrack"<<"\n";
    }*/
}

int Car::get_lives() {
    return *lives;
}

bool Car::get_mud_state() {
    if (!visibility) {
        visibility = true;
        return true;
    }
    return false;
}

Car::~Car() {
    delete (lives);
}

float Car::get_speed() {
    float angle = this->get_angle();
    b2Vec2 normal = get_forward_normal(angle);
    return b2Dot(m_body->GetLinearVelocity(), normal);
}

bool Car::isMoving() {
    return m_body->GetLinearVelocity().Length() > 1;
}

void Car::contact_limit() {
    std::cout << "car on limit\n";
}

