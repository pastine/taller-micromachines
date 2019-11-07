#include "server/Track.h"
#include "Box2D/Box2D.h"

Track::Track(b2Vec2 gravity) : world(b2World(gravity)) {
  b2BodyDef def;
  def.type = b2_staticBody;
  def.position.Set(0,0);
  b2Body* m_body = world.CreateBody(&def);
  b2PolygonShape track;
  b2FixtureDef fixture;
  fixture.isSensor = true;
  fixture.shape = &track;
  track.SetAsBox(40, 4.5, b2Vec2(0, 0), 0);//ground
  m_body->CreateFixture(&fixture);
  track.SetAsBox(40, 4.5, b2Vec2(0, 89), 0);//ceiling
  m_body->CreateFixture(&fixture);
  track.SetAsBox(4.5, 40, b2Vec2(-35.5, 44.5), 0);//left wall
  m_body->CreateFixture(&fixture);
  track.SetAsBox(4.5, 40, b2Vec2(35.5, 44.5), 0);//right wall
  m_body->CreateFixture(&fixture);
}

void Track::step(float32 timeStep, int32 velocityIt, int32 positionIt) {
  world.Step(timeStep, velocityIt, positionIt);
}
