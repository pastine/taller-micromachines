
#include "common/Serializer.h"
#include <server/Track.h>
#include <server/State.h>
#include <map>
#include "common/MoveType.h"

template<class T>
std::string Serializer<T>::serialize(T &block) {
    JSON j = serialize_to_json(block);
    return j.dump();
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
        std::cout<<msg<<'\n';
    } catch (std::runtime_error &e) {
        std::string err = "Error in Serializer<T>::send -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

template class Serializer<MoveType>;
template class Serializer<TrackData>; //Track
template class Serializer<std::map<int,int>>; //Races
template class Serializer<State>;
