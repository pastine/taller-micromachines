#include "server/Track.h"
#include "Box2D/Box2D.h"

Track::Track(b2World& world) {
  b2BodyDef def;
  def.type = b2_staticBody;
  def.position.Set(0,0);
  track = world.CreateBody(&def);
  b2PolygonShape walls;
  b2FixtureDef fixture;
  fixture.isSensor = true;
  fixture.shape = &walls;
  walls.SetAsBox( 40, 4.5, b2Vec2(4.5, 0), 0);//ground
  track->CreateFixture(&fixture);
  walls.SetAsBox( 40, 4.5, b2Vec2(4.5, 80), 0);//ceiling
  track->CreateFixture(&fixture);
  walls.SetAsBox( 4.5, 40, b2Vec2(-35.5, 40), 0);//left wall
  track->CreateFixture(&fixture);
  walls.SetAsBox( 4.5, 40, b2Vec2(44.5, 40), 0);//right wall
  track->CreateFixture(&fixture);

  b2CircleShape edge1;//down left edge
  edge1.m_p.Set(-35.5f, 0.0f);
  edge1.m_radius = 4.5f;
  b2FixtureDef fixture_edge1;
  fixture_edge1.shape = &edge1;
  fixture_edge1.isSensor = true;
  track->CreateFixture(&fixture_edge1);

  b2CircleShape edge2;//down right edge
  edge2.m_p.Set(44.5f, 0.0f);
  edge2.m_radius = 4.5f;
  b2FixtureDef fixture_edge2;
  fixture_edge2.shape = &edge2;
  fixture_edge2.isSensor = true;
  track->CreateFixture(&fixture_edge2);

  b2CircleShape edge3;//top right edge
  edge3.m_p.Set(44.5f, 80.0f);
  edge3.m_radius = 4.5f;
  b2FixtureDef fixture_edge3;
  fixture_edge3.shape = &edge3;
  fixture_edge3.isSensor = true;
  track->CreateFixture(&fixture_edge3);

  b2CircleShape edge4;//top left edge
  edge4.m_p.Set(-35.5f, 80.0f);
  edge4.m_radius = 4.5f;
  b2FixtureDef fixture_edge4;
  fixture_edge4.shape = &edge4;
  fixture_edge4.isSensor = true;
  track->CreateFixture(&fixture_edge4);
}

