#include <stdexcept>
#include "common/MoveSerializer.h"
#include "common/MoveType.h"

JSON MoveSerializer::serialize_to_json(MoveType &move) {
    switch (move) {
        case MoveType::UP:
            return "U";
        case MoveType::DOWN:
            return "D";
        case MoveType::LEFT:
            return "L";
        case MoveType::RIGHT:
            return "R";
        case MoveType::UPLEFT:
            return "Q";
        case MoveType::UPRIGHT:
            return "E";
        case MoveType::DOWNLEFT:
            return "Z";
        case MoveType::DOWNRIGHT:
            return "C";
    }
    std::string msg = "MoveSerializer::serialize -> Can't serialize";
    throw std::runtime_error(msg);
}

JSON MoveSerializer::deserialize(std::string &move) {
    JSON j = JSON::parse(move);
    switch (j.get<std::string>()[0]) {
        case 'U':
            return JSON(MoveType::UP);
        case 'D':
            return JSON(MoveType::DOWN);
        case 'L':
            return JSON(MoveType::LEFT);
        case 'R':
            return JSON(MoveType::RIGHT);
        case 'Q':
            return JSON(MoveType::UPLEFT);
        case 'E':
            return JSON(MoveType::UPRIGHT);
        case 'Z':
            return JSON(MoveType::DOWNLEFT);
        case 'C':
            return JSON(MoveType::DOWNRIGHT);
    }
    std::string msg = "MoveSerializer::deserialize -> Not recognized character";
    msg += ": ";
    msg.append(&move[0]);
    throw std::runtime_error(msg);
}
