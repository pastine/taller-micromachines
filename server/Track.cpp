#include "server/Track.h"
#include "Box2D/Box2D.h"
#define TRACK 0

Track::Track(b2World& world) {
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set(0, 0);
	track = world.CreateBody(&def);
	b2PolygonShape walls;
	b2FixtureDef fixture;
	fixture.isSensor = true;
	fixture.shape = &walls;

	for (float i = -31.05; i < 31.05; i += 6.9) {
		walls.SetAsBox(3.45, 2.75, b2Vec2(i, 0), 0);//ground
		track->CreateFixture(&fixture);
	}
	for (float i = -31.05; i < 31.05; i += 6.9) {
		walls.SetAsBox(3.45, 2.75, b2Vec2(i, 74.5), 0);//ceiling
		track->CreateFixture(&fixture);
	}
	for (float i = 6.2; i < 69; i += 6.9) {
		walls.SetAsBox(2.75, 3.45, b2Vec2(-37.25, i), 0);//left wall
		track->CreateFixture(&fixture);
	}
	for (float i = 6.2; i < 69; i += 6.9) {
		walls.SetAsBox(2.75, 3.45, b2Vec2(37.25, i), 0);//right wall
		track->CreateFixture(&fixture);
	}
	fixture.isSensor = true;
	int32 count = 3;

	//down right edge
	b2Vec2 vertices1[3];
	vertices1[0].Set(34.5f, 2.75f);
	vertices1[1].Set(34.5f, -2.75f);
	vertices1[2].Set(40.0f, 2.75f);
	b2PolygonShape edge1;
	edge1.Set(vertices1, count);
	b2FixtureDef fixture_edge1;
	fixture_edge1.shape = &edge1;
	fixture_edge1.isSensor = true;
	track->CreateFixture(&fixture_edge1);

	//down left edge
	b2Vec2 vertices2[3];
	vertices2[0].Set(-34.5f, 2.75f);
	vertices2[1].Set(-34.5f, -2.75f);
	vertices2[2].Set(-40.0f, 2.75f);
	b2PolygonShape edge2;
	edge2.Set(vertices2, count);
	b2FixtureDef fixture_edge2;
	fixture_edge2.shape = &edge2;
	fixture_edge2.isSensor = true;
	track->CreateFixture(&fixture_edge2);

	//top right edge
	b2Vec2 vertices3[3];
	vertices3[0].Set(-34.5f, 71.75f);
	vertices3[1].Set(-34.5f, 77.25f);
	vertices3[2].Set(-40.0f, 71.75f);
	b2PolygonShape edge3;
	edge3.Set(vertices3, count);
	b2FixtureDef fixture_edge3;
	fixture_edge3.shape = &edge3;
	fixture_edge3.isSensor = true;
	track->CreateFixture(&fixture_edge3);

	//top left edge
	b2Vec2 vertices4[3];
	vertices4[0].Set(34.5f, 71.75f);
	vertices4[1].Set(34.5f, 77.25f);
	vertices4[2].Set(40.0f, 71.75f);
	b2PolygonShape edge4;
	edge4.Set(vertices4, count);
	b2FixtureDef fixture_edge4;
	fixture_edge4.shape = &edge4;
	fixture_edge4.isSensor = true;
	track->CreateFixture(&fixture_edge4);

	track->SetUserData(this);
}

int Track::get_entity_type() {
	return TRACK;
}

