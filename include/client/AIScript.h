#ifndef TALLER_MICROMACHINES_AISCRIPT_H
#define TALLER_MICROMACHINES_AISCRIPT_H

#include <string>
#include "LuaFile.h"

const char DIRECTORY[] = "client/scripts/";
const char EXTENSION[] = ".lua";

class AIScript : public LuaFile {
public:
    explicit AIScript(std::string scriptName) : LuaFile(DIRECTORY + scriptName + EXTENSION) {}

    int index = 1;

    int getNextMove();

    int getMove(int i);
};


#endif //TALLER_MICROMACHINES_AISCRIPT_H
