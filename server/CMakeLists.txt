FILE(GLOB_RECURSE box2d_src
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/Box2D/*.h
        )

add_library(box2d STATIC ${box2d_src})

add_executable(server_test
        entities/Track.cpp ../include/server/Track.h
        entities/Car.cpp ../include/server/Car.h
        CarHandler.cpp ../include/server/CarHandler.h
        ClientProxy.cpp ../include/server/ClientProxy.h
        ClientAccepter.cpp ../include/server/ClientAccepter.h
        Server.cpp ../include/server/Server.h
        main.cpp Player.cpp ../include/server/Player.h
        Race.cpp ../include/server/Race.h
        ContactListener.cpp ../include/server/ContactListener.h
        Entity.cpp
        entities/Boost.cpp ../include/server/Boost.h
        entities/Health.cpp ../include/server/Health.h
        entities/Oil.cpp ../include/server/Oil.h
        entities/Mud.cpp ../include/server/Mud.h
        entities/Boulder.cpp ../include/server/Boulder.h
        StateHandler.cpp ../include/server/StateHandler.h
        ../include/server/Entity.h
        entities/Limit.cpp ../include/server/Limit.h
        State.cpp ../include/server/State.h Environment.cpp ../include/server/Environment.h TrackStructure.cpp ../include/server/TrackStructure.h TrackData.cpp ../include/server/TrackData.h Mod.cpp ../include/server/Mod.h)

add_library(OneLife SHARED mods/libOneLife.cpp)
add_library(AlwaysMud SHARED mods/libAlwaysMud.cpp)


target_link_libraries(server_test box2d)
target_link_libraries(server_test OneLife ${CMAKE_DL_LIBS})
target_link_libraries(server_test AlwaysMud ${CMAKE_DL_LIBS})
