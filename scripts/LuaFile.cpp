#include "scripts/LuaFile.h"

LuaFile::LuaFile(std::string filename) {
    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, filename.c_str());
    lua_pcall(L, 0, 0, 0);
}

LuaFile::~LuaFile() {
    if (L) lua_close(L);
}

LuaRef LuaFile::getVariable(std::string variableName) {
    return getGlobal(L, variableName.c_str());
}

LuaRef LuaFile::callFunction(std::string functionName, std::vector<int> args) {
    LuaRef function = getGlobal(L, functionName.c_str());
    return function(args);
}
