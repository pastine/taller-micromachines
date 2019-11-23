#include "server/Entity.h"


b2Vec2 Entity::get_position() {
    return m_body->GetPosition();
}
