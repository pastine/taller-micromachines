FILE(GLOB_RECURSE box2d_src
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.h
        )

add_library(box2d STATIC ${box2d_src})

add_executable(server_test
        simulator.cpp
        track.cpp ../include/server/track.h
        car.cpp ../include/server/car.h
        circuit_generator.cpp ../include/server/circuit_generator.h
        event_listener.cpp ../include/server/event_listener.h
        car_handler.cpp ../include/server/car_handler.h
        event_handler.cpp ../include/server/event_handler.h)

target_link_libraries(server_test box2d)
