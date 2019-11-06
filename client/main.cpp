//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <QtWidgets/QApplication>
#include <client/ServerProxy.h>
#include <common/ProtectedQueue.h>
#include <client/ThStateReceiver.h>
#include <client/ThFrameDrawer.h>
#include <map>
#include "client/SDLException.h"
#include "client/Launcher.h"
#include "client/Audio.h"

int main(int argc, char** argv) {
    try {
        std::string host(argv[1]);
        std::string service(argv[2]);
        ServerProxy server(host, service);

        std::map<std::string,int> races_ids_players = server.handshake();
        QApplication app(argc, argv);
        int retValue = -1;
        Launcher launcher(races_ids_players, &retValue);
        launcher.show();
        app.exec();

        server.handshake_answer(retValue);

        ProtectedQueue queue(10);

        Audio audio;

        ThStateReceiver state_receiver(&server, &queue);
        ThFrameDrawer frame_drawer(&queue);
        state_receiver.start();
        frame_drawer.start();

        //Camera cam;
        //WorldEntities entities;

        bool running = true;
        while (running) {
            SDL_Event event;

            /*
            cam.prepare_frame();

            entities.clean();
            entities.put(WorldEntities::Entity::CAR, 100, 700 - (i % 700), 0);
            entities.put(WorldEntities::Entity::OIL, 50, 50);
            entities.render(cam);
            */

            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                audio.play();
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
            //cam.show_frame();
            SDL_Delay(50);
        }
        state_receiver.stop();
        frame_drawer.stop();
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}
