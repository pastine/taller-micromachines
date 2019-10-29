//
// Created by casimiro on 29/10/19.
//

#include "common/MoveSerializer.h"

using MoveType

std::string MoveSerializer::serialize(MoveType &move) {
    switch (move) {
        case UP:
            return "U";
        case DOWN:
            return "D";
        case LEFT:
            return "L";
        case RIGHT:
            return "R";
    }
}