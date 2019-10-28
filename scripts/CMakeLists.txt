include_directories(/usr/include/lua5.3)

add_executable(scripts_test
        helloWorld.lua
        scriptsTests.cpp
        LuaFile.cpp ../include/scripts/LuaFile.h
        ../include/scripts/AIScript.h
        )

target_link_libraries(scripts_test lua5.3)