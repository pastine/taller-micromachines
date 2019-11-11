#include <server/Car.h>
#include <iostream>
#include <server/Element.h>
#include "server/ContactListener.h"

void ContactListener::BeginContact(b2Contact *contact) {
  std::cout<<"entre a begin\n";
	bool A_is_sensor = contact->GetFixtureA()->IsSensor();
	bool B_is_sensor = contact->GetFixtureB()->IsSensor();
	if(A_is_sensor && B_is_sensor) { return;}
	std::cout<<"no son dos sensores\n";
  void* A = contact->GetFixtureA()->GetBody()->GetUserData();
	int A_ID = static_cast<Entity*>(A)->get_entity_type();
	void* B = contact->GetFixtureA()->GetBody()->GetUserData();
	int B_ID = static_cast<Entity*>(B)->get_entity_type();
	std::cout<<"encuentro el id\n";
	if (A_ID == 1 && B_ID == 1){
		std::cout<<"son dos autos\n";
		static_cast<Car*>(A)->start_contact(B_ID);
		static_cast<Car*>(B)->start_contact(A_ID);
	} else if (A_ID == 1) {
		std::cout<<"a es auto\n";
		static_cast<Car*>(A)->start_contact(B_ID);
		if (B_ID != 0) {
			std::cout<<"no es pista\n";
			static_cast<Element*>(B)->start_contact();
		}
	} else {
		std::cout<<"b es auto\n";
		static_cast<Car*>(B)->start_contact(A_ID);
		if (A_ID != 0) {
			std::cout<<"no es pista\n";
			static_cast<Element*>(A)->start_contact();
		}
	}
	std::cout<<"termino begin\n";
}

void ContactListener::EndContact(b2Contact *contact) {
  std::cout<<"entre a end\n";
	bool A_is_sensor = contact->GetFixtureA()->IsSensor();
	bool B_is_sensor = contact->GetFixtureB()->IsSensor();
	if(A_is_sensor && B_is_sensor) { return;}
	void* A = contact->GetFixtureA()->GetBody()->GetUserData();
	int A_ID = static_cast<Entity*>(A)->get_entity_type();
	void* B = contact->GetFixtureA()->GetBody()->GetUserData();
	int B_ID = static_cast<Entity*>(B)->get_entity_type();
	if (A_ID == 1 && B_ID == 1){
		static_cast<Car*>(A)->end_contact(B_ID);
		static_cast<Car*>(B)->end_contact(A_ID);
	} else if (A_ID == 1) {
		static_cast<Car*>(A)->end_contact(B_ID);
		if (B_ID != 0) {
			static_cast<Element*>(B)->end_contact();
		}
	} else {
		static_cast<Car*>(B)->end_contact(A_ID);
		if (A_ID != 0) {
			static_cast<Element*>(A)->end_contact();
		}
	}
}
