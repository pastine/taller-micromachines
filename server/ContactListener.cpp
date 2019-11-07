#include <server/Car.h>
#include <iostream>
#include "server/ContactListener.h"

void ContactListener::BeginContact(b2Contact *contact) {
  std::cout<<"entre a begin\n";
  bool A_is_sensor = contact->GetFixtureA()->IsSensor();
  bool B_is_sensor = contact->GetFixtureB()->IsSensor();
  if (A_is_sensor || B_is_sensor) {
    if (A_is_sensor) {
      void* B_body = contact->GetFixtureB()->GetBody()->GetUserData();
      static_cast<Car*>(B_body)->on_track();
    } else {
      void* A_body = contact->GetFixtureA()->GetBody()->GetUserData();
      static_cast<Car*>(A_body)->on_track();
    }
    return;
  }
  void* A_body = contact->GetFixtureA()->GetBody()->GetUserData();
  void* B_body = contact->GetFixtureB()->GetBody()->GetUserData();
  if (A_body && B_body) {
    static_cast<Car*>(A_body)->start_contact();
    static_cast<Car*>(B_body)->start_contact();
  }
}

void ContactListener::EndContact(b2Contact *contact) {
  std::cout<<"entre a end\n";
  bool A_is_sensor = contact->GetFixtureA()->IsSensor();
  bool B_is_sensor = contact->GetFixtureB()->IsSensor();
  if (A_is_sensor || B_is_sensor) {
    if (A_is_sensor) {
      void* B_body = contact->GetFixtureB()->GetBody()->GetUserData();
      static_cast<Car*>(B_body)->off_track();
    } else {
      void* A_body = contact->GetFixtureA()->GetBody()->GetUserData();
      static_cast<Car*>(A_body)->off_track();
    }
    return;
  }
  void* A_body = contact->GetFixtureA()->GetBody()->GetUserData();
  void* B_body = contact->GetFixtureB()->GetBody()->GetUserData();
  if (A_body && B_body) {
    static_cast<Car*>(A_body)->end_contact();
    static_cast<Car*>(B_body)->end_contact();
  }
}
