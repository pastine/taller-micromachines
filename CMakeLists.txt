cmake_minimum_required(VERSION 3.14)
project(taller_micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

include_directories(include/)
include_directories(libs/)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(client_src)
add_subdirectory(server_src)

add_library(common_src STATIC
        common_src/Communication.cpp include/common/Communication.h
        common_src/serializers/MoveSerializer.cpp include/common/MoveSerializer.h
        common_src/serializers/StateSerializer.cpp include/common/StateSerializer.h
        common_src/Socket.cpp include/common/Socket.h
        common_src/Thread.cpp include/common/Thread.h
        include/common/json.h
        include/common/MoveType.h
        common_src/serializers/RacesSerializer.cpp include/common/RacesSerializer.h common_src/serializers/TrackSerializer.cpp include/common/TrackSerializer.h include/common/Constants.h common_src/ClosedQueueException.cpp include/common/ClosedQueueException.h common_src/ProtectedQueue.cpp include/common/ProtectedQueue.h include/common/CommunicationConstants.h
        common_src/Serializer.cpp include/common/Serializer.h
        )

target_link_libraries(server common_src)
target_link_libraries(client common_src)

set(CPPLINT_FILTER_OPTIONS
        "-,+build/class,+build/deprecated,+build/include_what_you_use,+build/printf_format,\
        +readability/braces,+readability/check,+readability/fn_size,\
        +readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
        +runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,\
        +runtime/memset,+runtime/operator,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
        +whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,\
        +whitespace/newline,+whitespace/parens,+whitespace/semicolon"
        )

add_custom_target(lint_common
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/common_src/"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/common/"
        )

add_custom_target(lint_server
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/server_src/server_src"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/server/"
        )

add_custom_target(lint_client
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/client_src/client_src"
        COMMAND cpplint --extensions=h,hpp,c,cpp --filter=${CPPLINT_FILTER_OPTIONS} --linelength=100 --recursive "${PROJECT_SOURCE_DIR}/include/client/"
        )


add_dependencies(common_src lint_common)
add_dependencies(client lint_client)
add_dependencies(server lint_server)
