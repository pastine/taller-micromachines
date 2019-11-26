
#include "client/AIScript.h"

int AIScript::getNextMove() {
    int size = callFunction("getSize", {});
    if (index > size) index = 1;
    return getMove(index++);
}


int AIScript::getMove(int i) {
    int move = callFunction("getMove", {i});
    return move;
}
