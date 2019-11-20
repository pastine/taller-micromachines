find_package(Qt5Widgets)
include_directories(/usr/include/lua5.3)

add_executable(client_test
        main.cpp
        sdl_wrappers/SDLWindow.cpp ../include/client/SDLWindow.h
        sdl_wrappers/SDLException.cpp ../include/client/SDLException.h
        sdl_wrappers/SDLTextureLoader.cpp ../include/client/SDLTextureLoader.h
        sdl_wrappers/SDLTexture.cpp ../include/client/SDLTexture.h
        sdl_wrappers/Area.cpp ../include/client/Area.h
        entities/Car.cpp ../include/client/Car.h
        entities/CarFrameResolver.cpp ../include/client/CarFrameResolver.h
        entities/Boulder.cpp ../include/client/Boulder.h
        ../include/client/Renderizable.h
        entities/Oil.cpp ../include/client/Oil.h
        entities/Mud.cpp ../include/client/Mud.h
        Camera.cpp ../include/client/Camera.h
        sdl_wrappers/StaticRenderizable.cpp ../include/client/StaticRenderizable.h
        WorldEntities.cpp ../include/client/WorldEntities.h
        Launcher.cpp
        scripts/bot.lua
        scripts/LuaFile.cpp ../../include/client/LuaFile.h
        ../../include/client/AIScript.h
        ServerProxy.cpp ../include/client/ServerProxy.h ThStateReceiver.cpp ../include/client/ThStateReceiver.h ThFrameDrawer.cpp ../include/client/ThFrameDrawer.h
        sdl_wrappers/Audio.cpp ../include/client/Audio.h
        entities/StraightRoad.cpp ../include/client/StraightRoad.h entities/CurvedRoad.cpp ../include/client/CurvedRoad.h entities/Boost.cpp ../include/client/Boost.h entities/Heart.cpp ../include/client/Heart.h CarLivesDrawer.cpp ../include/client/CarLivesDrawer.h scripts/AIScript.cpp sdl_wrappers/SDLText.cpp ../include/client/SDLText.h entities/MudSplatter.cpp entities/MudSplatter.h)

target_link_libraries(client_test SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_link_libraries(client_test Qt5::Widgets)
target_link_libraries(client_test lua5.3)
