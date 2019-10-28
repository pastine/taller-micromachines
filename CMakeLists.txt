cmake_minimum_required(VERSION 3.10)
project(taller_micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

include_directories(include/)
include_directories(libs/)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(scripts)
add_subdirectory(mods)
add_subdirectory(client)
add_subdirectory(server)

set(CPPLINT_FILTER_OPTIONS
        "-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
        +readability/braces,+readability/check,+readability/fn_size,\
        +readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
        +runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,\
        +runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
        +whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,\
        +whitespace/newline,+whitespace/parens,+whitespace/semicolon"
        )


add_custom_target(lint_headers
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )

add_custom_target(lint_client
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${CMAKE_CURRENT_SOURCE_DIR}/client/"
        )

add_custom_target(lint_server
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${CMAKE_CURRENT_SOURCE_DIR}/server/"
        )

add_custom_target(lint_mods
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${CMAKE_CURRENT_SOURCE_DIR}/mods/"
        )

add_custom_target(lint_scripts
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${CMAKE_CURRENT_SOURCE_DIR}/scripts/"
        )

#add_dependencies(scripts_test lint_headers)
#add_dependencies(scripts_test lint_scripts)
#add_dependencies(mods_test lint_headers)
#add_dependencies(mods_test lint_mods)
#add_dependencies(client_test lint_headers)
#add_dependencies(client_test lint_client)
#add_dependencies(server_test lint_headers)
#add_dependencies(server_test lint_server)
