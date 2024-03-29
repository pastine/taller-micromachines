#include <server/Car.h>
#include "server/ContactListener.h"

void ContactListener::BeginContact(b2Contact *contact) {
    bool A_is_sensor = contact->GetFixtureA()->IsSensor();
    bool B_is_sensor = contact->GetFixtureB()->IsSensor();
    if (A_is_sensor && B_is_sensor) { return; }
    void *A = contact->GetFixtureA()->GetBody()->GetUserData();
    int A_ID = static_cast<Entity *>(A)->get_entity_type();
    void *B = contact->GetFixtureB()->GetBody()->GetUserData();
    int B_ID = static_cast<Entity *>(B)->get_entity_type();
    if (A_ID == 1 && B_ID == 1) {
        static_cast<Car *>(A)->start_contact(B_ID);
        static_cast<Car *>(B)->start_contact(A_ID);
    } else if (A_ID == 1) {
        static_cast<Car *>(A)->start_contact(B_ID);
        if (B_ID != 0) {
            static_cast<Entity *>(B)->start_contact();
        }
    } else if (B_ID == 1) {
        static_cast<Car *>(B)->start_contact(A_ID);
        if (A_ID != 0) {
            static_cast<Entity *>(A)->start_contact();
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    bool A_is_sensor = contact->GetFixtureA()->IsSensor();
    bool B_is_sensor = contact->GetFixtureB()->IsSensor();
    if (A_is_sensor && B_is_sensor) { return; }
    void *A = contact->GetFixtureA()->GetBody()->GetUserData();
    int A_ID = static_cast<Entity *>(A)->get_entity_type();
    void *B = contact->GetFixtureB()->GetBody()->GetUserData();
    int B_ID = static_cast<Entity *>(B)->get_entity_type();
    if (A_ID == 1 && B_ID == 1) {
        static_cast<Car *>(A)->end_contact(B_ID);
        static_cast<Car *>(B)->end_contact(A_ID);
    } else if (A_ID == 1) {
        static_cast<Car *>(A)->end_contact(B_ID);
        if (B_ID != 0) {
            static_cast<Entity *>(B)->end_contact();
        }
    } else if (B_ID == 1) {
        static_cast<Car *>(B)->end_contact(A_ID);
        if (A_ID != 0) {
            static_cast<Entity *>(A)->end_contact();
        }
    }
}
