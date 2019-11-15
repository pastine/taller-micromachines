cmake_minimum_required(VERSION 3.14)
project(taller_micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

include_directories(include/)
include_directories(libs/)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(mods)
add_subdirectory(client)
add_subdirectory(server)

add_library(common STATIC
        common/Communication.cpp include/common/Communication.h
        common/MoveSerializer.cpp include/common/MoveSerializer.h
        common/StateSerializer.cpp include/common/StateSerializer.h
        common/Socket.cpp include/common/Socket.h
        common/Thread.cpp include/common/Thread.h
        include/common/json.h
        include/common/MoveType.h
        common/ProtectedQueue.cpp include/common/ProtectedQueue.h
        common/RacesSerializer.cpp include/common/RacesSerializer.h common/TrackSerializer.cpp include/common/TrackSerializer.h common/ProtectedQueueState.cpp include/common/ProtectedQueueState.h include/common/Constants.h common/ClosedQueueException.cpp common/ClosedQueueException.h)

target_link_libraries(server_test common)
target_link_libraries(client_test common)

set(CPPLINT_FILTER_OPTIONS
        "-,+build/class,+build/deprecated,+build/include_what_you_use,+build/printf_format,\
        +readability/braces,+readability/check,+readability/fn_size,\
        +readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
        +runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,\
        +runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
        +whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,\
        +whitespace/newline,+whitespace/parens,+whitespace/semicolon"
        )

add_custom_target(lint_common
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/common/"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/common/"
        )

add_custom_target(lint_server
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/server/"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/server/"
        )

add_custom_target(lint_client
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/client/"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/client/"
        )

add_custom_target(lint_mods
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/mods/"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/mods/"
        )


add_dependencies(common lint_common)
add_dependencies(mods_test lint_mods)
add_dependencies(client_test lint_client)
add_dependencies(server_test lint_server)
