
#ifndef TALLER_MICROMACHINES_SERIALIZER_H
#define TALLER_MICROMACHINES_SERIALIZER_H

#include <string>
#include "json.h"
#include "MoveType.h"
#include "Communication.h"

template<class T>
class Serializer {
public:
    virtual std::string serialize(T &block);

    virtual JSON deserialize(std::string &str);

    virtual JSON serialize_to_json(T &block) = 0;

    virtual JSON receive(Communication &comm);

    virtual void send(Communication &comm, T &block);
};

#endif //TALLER_MICROMACHINES_SERIALIZER_H
