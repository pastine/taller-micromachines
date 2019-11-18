FILE(GLOB_RECURSE box2d_src
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.h
        )

add_library(box2d STATIC ${box2d_src})

add_executable(server_test
        Track.cpp ../include/server/Track.h
        Car.cpp ../include/server/Car.h
        ../include/server/circuit_generator.h
        CarHandler.cpp ../include/server/CarHandler.h
        ClientProxy.cpp ../include/server/ClientProxy.h
        ClientAccepter.cpp ../include/server/ClientAccepter.h
        Server.cpp ../include/server/Server.h
        main.cpp Player.cpp ../include/server/Player.h
        Race.cpp ../include/server/Race.h
        ContactListener.cpp ../include/server/ContactListener.h
        Element.cpp ../include/server/Element.h
        Boost.cpp ../include/server/Boost.h
        Health.cpp ../include/server/Health.h
        Oil.cpp ../include/server/Oil.h
        Mud.cpp ../include/server/Mud.h
        Stone.cpp ../include/server/Stone.h
        StateHandler.cpp ../include/server/StateHandler.h
        ../include/server/Entity.h
        Limit.cpp ../include/server/Limit.h)

add_library(MiddleManState SHARED mods/libMiddleManState.cpp)


target_link_libraries(server_test box2d)
target_link_libraries(server_test MiddleManState ${CMAKE_DL_LIBS})
