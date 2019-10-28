#ifndef TALLER_MICROMACHINES_LUAFILE_H
#define TALLER_MICROMACHINES_LUAFILE_H

#include <string>

extern "C" {
# include "lua5.3/lua.h"
# include "lua5.3/lauxlib.h"
# include "lua5.3/lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

using namespace luabridge;

class LuaFile {
public:
    LuaFile(std::string filename);

    ~LuaFile();

    lua_State *L;

    LuaRef callFunction(std::string functionName, std::vector<int> args);

    LuaRef getVariable(std::string variableName);
};


#endif //TALLER_MICROMACHINES_LUAFILE_H
