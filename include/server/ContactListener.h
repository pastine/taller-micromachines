#ifndef TALLER_MICROMACHINES_CONTACTLISTENER_H
#define TALLER_MICROMACHINES_CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener{
public:
  ContactListener(){}

  virtual void begin_contact(b2Contact* contact);

  virtual void end_contact(b2Contact* contact);

  ~ContactListener(){}
};


#endif //TALLER_MICROMACHINES_CONTACTLISTENER_H
