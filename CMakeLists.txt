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

########## CLIENT ##########

########## MODS ##########
add_library(HelloWorld SHARED
        mods/libHelloWorld.cpp
        )

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