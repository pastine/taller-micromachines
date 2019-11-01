find_package(Qt5Widgets)

qt5_wrap_ui(UIS_HEADERS
        Launcher.ui
        )

qt5_add_resources(RESOURCES_SRC
        launcherBanner.qrc
        )


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
        ServerProxy.cpp ../include/client/ServerProxy.h ThStateReceiver.cpp ../include/client/ThStateReceiver.h ThFrameDrawer.cpp ThFrameDrawer.h)

target_link_libraries(client_test SDL2 SDL2_image)
target_link_libraries(client_test Qt5::Widgets)
