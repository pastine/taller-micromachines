#include <server/Car.h>
#include "server/ContactListener.h"

void ContactListener::begin_contact(b2Contact* contact) {
  void* A_body = contact->GetFixtureA()->GetBody()->GetUserData();
  void* B_body = contact->GetFixtureB()->GetBody()->GetUserData();
  if (A_body && B_body) {
    static_cast<Car*>(A_body)->start_contact();
    static_cast<Car*>(B_body)->start_contact();
  }
}

void ContactListener::end_contact(b2Contact* contact) {
  void* A_body = contact->GetFixtureA()->GetBody()->GetUserData();
  void* B_body = contact->GetFixtureB()->GetBody()->GetUserData();
  if (A_body && B_body) {
    static_cast<Car*>(A_body)->end_contact();
    static_cast<Car*>(B_body)->end_contact();
  }
}
