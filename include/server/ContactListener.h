#ifndef TALLER_MICROMACHINES_CONTACTLISTENER_H
#define TALLER_MICROMACHINES_CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener {
public:
    virtual void BeginContact(b2Contact *contact);

    virtual void EndContact(b2Contact *contact);
};


#endif //TALLER_MICROMACHINES_CONTACTLISTENER_H
