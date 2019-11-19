#ifndef TALLER_MICROMACHINES_ENTITY_H
#define TALLER_MICROMACHINES_ENTITY_H


class Entity {
public:
    b2Body *m_body;

    virtual int get_entity_type() = 0;

    virtual b2Vec2 get_position() = 0;
};

#endif //TALLER_MICROMACHINES_ENTITY_H
