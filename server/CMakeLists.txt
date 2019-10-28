FILE(GLOB_RECURSE box2d_src
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.h
        )

add_library(box2d STATIC ${box2d_src})

add_executable(server_test
        simulator.cpp
        track.cpp track.h
        car.cpp car.h
        circuit_generator.cpp circuit_generator.h
        event_listener.cpp event_listener.h
        car_handler.cpp car_handler.h
        event_handler.cpp event_handler.h)

target_link_libraries(server_test box2d)
