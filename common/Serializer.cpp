
#include "common/Serializer.h"
#include <server/Track.h>
#include <map>
#include <server/Player.h>
#include "common/MoveType.h"

template<class T>
std::string Serializer<T>::serialize(T &block) {
    JSON j =
            serialize_to_json(block);
    return serialize(j);
}

template<class T>
JSON Serializer<T>::deserialize(std::string &str) {
    return JSON::parse(str.data());
}

template<class T>
JSON Serializer<T>::receive(Communication &comm) {
    try {
        std::string msg;
        comm.receive_msg(msg);
        return deserialize(msg);
    } catch (std::runtime_error &e) {
        std::string err = "Error in Serializer<T>::receive -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

template<class T>
void Serializer<T>::send(Communication &comm, T &block) {
    try {
        std::string msg;
        msg = serialize(block);
        comm.send_msg(msg);
    } catch (std::runtime_error &e) {
        std::string err = "Error in Serializer<T>::send -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

template<class T>
std::string Serializer<T>::serialize(JSON &block) {
    return block.dump();
}

template class Serializer<MoveType>;
template class Serializer<Track>;
template class Serializer<std::map<int,int>>; //Races
template class Serializer<Player>;
