#ifndef TALLER_MICROMACHINES_AISCRIPT_H
#define TALLER_MICROMACHINES_AISCRIPT_H

#include <string>
#include "LuaFile.h"

const char DIRECTORY[] = "scripts/";
const char EXTENSION[] = ".lua";

class AIScript : public LuaFile {
public:
    explicit AIScript(std::string scriptName) : LuaFile(DIRECTORY + scriptName + EXTENSION) {}
};


#endif //TALLER_MICROMACHINES_AISCRIPT_H
