add_executable(client_test
        main.cpp
        SDLWindow.cpp SDLWindow.h
        SDLException.cpp SDLException.h
        SDLTextureLoader.cpp SDLTextureLoader.h
        SDLTexture.cpp SDLTexture.h
        Area.cpp Area.h
        Car.cpp Car.h
        CarFrameResolver.cpp CarFrameResolver.h
        Boulder.cpp Boulder.h
        Renderizable.h
        Oil.cpp Oil.h
        Mud.cpp Mud.h
        Camara.cpp Camara.h
        StaticRenderizable.cpp StaticRenderizable.h
        WorldEntities.cpp WorldEntities.h)

target_link_libraries(client_test SDL2 SDL2_image)
