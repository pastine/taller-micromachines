#ifndef TALLER_MICROMACHINES_AISCRIPT_H
#define TALLER_MICROMACHINES_AISCRIPT_H

#include <string>
#include "LuaFile.h"

const std::string DIRECTORY = "scripts/";
const std::string EXTENSION = ".lua";

class AIScript : public LuaFile {
public:
    AIScript(std::string scriptName) : LuaFile(DIRECTORY + scriptName + EXTENSION) {}
};


#endif //TALLER_MICROMACHINES_AISCRIPT_H
