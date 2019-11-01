//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <QtWidgets/QApplication>
#include <client/ServerProxy.h>
#include <common/ProtectedQueue.h>
#include "client/SDLException.h"
#include "client/Camera.h"
#include "client/WorldEntities.h"
#include "client/Launcher.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Launcher launcher;
    launcher.show();
    app.exec();


    try {
        std::string host(argv[1]);
        std::string service(argv[2]);
        ServerProxy server(host, service);

        ProtectedQueue queue(10);

        Camera cam;
        WorldEntities entities;

        auto i = 0;
        bool running = true;
        while (running) {
            SDL_Event event;

            cam.prepare_frame();

            entities.clean();
            entities.put(WorldEntities::Entity::CAR, 100, 700 - (i % 700), 0);
            entities.put(WorldEntities::Entity::OIL, 50, 50);
            entities.render(cam);

            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                server.player_move(MoveType::LEFT);
                                break;
                            case SDLK_RIGHT:
                                server.player_move(MoveType::RIGHT);
                                break;
                            case SDLK_UP:
                                server.player_move(MoveType::UP);
                                break;
                            case SDLK_DOWN:
                                server.player_move(MoveType::DOWN);
                                break;
                        }
                    }
                }
            }
            cam.show_frame();
            SDL_Delay(50);
            i += 10;
        }
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}
