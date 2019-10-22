cmake_minimum_required(VERSION 3.10)
project(taller_micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

include_directories(include/)
include_directories(libs/)
include_directories(/usr/include/lua5.3)

########## SERVER ##########

FILE(GLOB_RECURSE box2d_src
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.h
)
add_library(box2d STATIC
        ${box2d_src})

add_executable(server_test
        server/simulator.cpp
        server/track.cpp server/track.h
        server/car.cpp server/car.h
        server/circuit_generator.cpp server/circuit_generator.h
)

target_link_libraries(server_test box2d)
########## CLIENT ##########

add_executable(client_test
        client/main.cpp
        client/SDLWindow.cpp client/SDLWindow.h
        client/SDLException.cpp client/SDLException.h
        client/SDLTextureLoader.cpp client/SDLTextureLoader.h
        client/SDLTexture.cpp client/SDLTexture.h
        client/Area.cpp client/Area.h
        client/Car.cpp client/Car.h
        client/CarFrameResolver.cpp client/CarFrameResolver.h
        client/Boulder.cpp client/Boulder.h)

target_link_libraries(client_test SDL2 SDL2_image)

########## MODS ##########
add_library(HelloWorld SHARED
        mods/libHelloWorld.cpp)


add_executable(mods_tests
        mods/modsTests.cpp
        )

target_link_libraries(mods_tests HelloWorld ${CMAKE_DL_LIBS})
########## SCRIPTS ##########

add_executable(scripts_tests
        scripts/helloWorld.lua
        scripts/scriptsTests.cpp
        scripts/LuaFile.cpp scripts/LuaFile.h
        scripts/AIScript.h
        )
target_link_libraries(scripts_tests lua5.3)

########## CPPLINT STUFF ##########

set(CPPLINT_FILTER_OPTIONS
        "-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
        +readability/braces,+readability/check,+readability/fn_size,\
        +readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
        +runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,\
        +runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
        +whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,\
        +whitespace/newline,+whitespace/parens,+whitespace/semicolon"
        )

set(CMAKE_CXX_CPPLINT "cpplint;--extensions=c,cpp;--filter=${CPPLINT_FILTER_OPTIONS}")

add_custom_target(lint_headers
        COMMAND cpplint --filter=${CPPLINT_FILTER_OPTIONS} --recursive "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )

add_dependencies(scripts_tests lint_headers)
add_dependencies(mods_tests lint_headers)