find_package(Qt5Widgets)

add_executable(client_test
        main.cpp
        SDLWindow.cpp ../include/client/SDLWindow.h
        SDLException.cpp ../include/client/SDLException.h
        SDLTextureLoader.cpp ../include/client/SDLTextureLoader.h
        SDLTexture.cpp ../include/client/SDLTexture.h
        Area.cpp ../include/client/Area.h
        Car.cpp ../include/client/Car.h
        CarFrameResolver.cpp ../include/client/CarFrameResolver.h
        Boulder.cpp ../include/client/Boulder.h
        ../include/client/Renderizable.h
        Oil.cpp ../include/client/Oil.h
        Mud.cpp ../include/client/Mud.h
        Camera.cpp ../include/client/Camera.h
        StaticRenderizable.cpp ../include/client/StaticRenderizable.h
        WorldEntities.cpp ../include/client/WorldEntities.h
        Launcher.cpp
        ${UIS_HEADERS}
        ${RESOURCES_SRC}
        ServerProxy.cpp ../include/client/ServerProxy.h ThStateReceiver.cpp ../include/client/ThStateReceiver.h ThFrameDrawer.cpp ../include/client/ThFrameDrawer.h
        Audio.cpp ../include/client/Audio.h
        StraightRoad.cpp ../include/client/StraightRoad.h CurvedRoad.cpp ../include/client/CurvedRoad.h Boost.cpp ../include/client/Boost.h Heart.cpp ../include/client/Heart.h)

target_link_libraries(client_test SDL2 SDL2_image SDL2_mixer)
target_link_libraries(client_test Qt5::Widgets)
