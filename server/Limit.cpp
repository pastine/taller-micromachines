#include <iostream>
#include "server/Limit.h"

Limit::Limit(b2World &world) {
	b2BodyDef def_box;
	def_box.type = b2_staticBody;
	def_box.position.Set(0,0);
	limit = world.CreateBody(&def_box);
	b2PolygonShape limit_box;
	b2FixtureDef fixture_box_def;
	fixture_box_def.shape = &limit_box;
	limit_box.SetAsBox(50, 1, b2Vec2(0, -10), 0);//ground
	limit->CreateFixture(&fixture_box_def);
	limit_box.SetAsBox(50, 1, b2Vec2(0, 90), 0);//ceiling
	limit->CreateFixture(&fixture_box_def);
	limit_box.SetAsBox(1, 50, b2Vec2(-50, 40), 0);//left wall
	limit->CreateFixture(&fixture_box_def);
	limit_box.SetAsBox(1, 50, b2Vec2(50, 40), 0);//right wall
	limit->CreateFixture(&fixture_box_def);
	limit->SetUserData(this);
}

void Limit::start_contact() {
	std::cout<<"borde\n";
}

void Limit::end_contact() {
}

b2Vec2 Limit::get_position() {
	return b2Vec2(0,0);
}

int Limit::get_entity_type() {
	return LIMIT;
}

void Limit::destroy() {
}
