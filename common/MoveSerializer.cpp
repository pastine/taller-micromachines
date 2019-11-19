#include <stdexcept>
#include "common/MoveSerializer.h"
#include "common/MoveType.h"


char MoveSerializer::serialize(MoveType &move) {
    switch (move) {
        case MoveType::UP:
            return 'U';
        case MoveType::DOWN:
            return 'D';
        case MoveType::LEFT:
            return 'L';
        case MoveType::RIGHT:
            return 'R';
        case MoveType::UPLEFT:
            return 'Q';
        case MoveType::UPRIGHT:
            return 'E';
        case MoveType::DOWNLEFT:
            return 'Z';
        case MoveType::DOWNRIGHT:
            return 'C';
    }
    std::string msg = "MoveSerializer::serialize -> Can't serialize";
    throw std::runtime_error(msg);
}

MoveType MoveSerializer::deserialize(char move) {
    switch (move) {
        case 'U':
            return MoveType::UP;
        case 'D':
            return MoveType::DOWN;
        case 'L':
            return MoveType::LEFT;
        case 'R':
            return MoveType::RIGHT;
        case 'Q':
            return MoveType::UPLEFT;
        case 'E':
            return MoveType::UPRIGHT;
        case 'Z':
            return MoveType::DOWNLEFT;
        case 'C':
            return MoveType::DOWNRIGHT;
    }
    std::string msg = "MoveSerializer::deserialize -> Not recognized character";
    msg += ": ";
    msg.append(&move);
    throw std::runtime_error(msg);
}
