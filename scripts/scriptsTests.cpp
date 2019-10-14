extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include <iostream>

using namespace luabridge;

int main() {
    lua_State *L = luaL_newstate();
    luaL_dofile(L, "scripts/helloWorld.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef s = getGlobal(L, "testString");
    std::string luaString = s.cast<std::string>();
    std::cout << luaString << std::endl;
}