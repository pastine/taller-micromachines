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
#include "client/AIScript.h"

void send_moves(ServerProxy *server, bool up, bool down, bool left, bool right) {
    if (left && up) server->player_move(MoveType::UPLEFT);
    else if (right && up) server->player_move(MoveType::UPRIGHT);
    else if (up) server->player_move(MoveType::UP);
    else if (down) server->player_move(MoveType::DOWN);
    else if (right) server->player_move(MoveType::RIGHT);
    else if (left) server->player_move(MoveType::LEFT);
}

int main(int argc, char **argv) {
    try {
        std::string host(argv[1]);
        std::string service(argv[2]);
        ServerProxy server(host, service);

        std::map<std::string, int> races_ids_players = server.handshake();
        int retValue = -1;
        bool playwithbot = 0;
        QApplication app(argc, argv);
        Launcher launcher(races_ids_players, &retValue, &playwithbot);
        launcher.show();
        app.exec();

        JSON map;
        server.handshake_answer(retValue, &map);

        ProtectedQueue<JSON> queue;

        //Audio audio;

        ThStateReceiver state_receiver(&server, &queue);
        ThFrameDrawer frame_drawer(&queue, map);
        state_receiver.start();
        frame_drawer.start();

        bool running = true;
        bool up = false, down = false, left = false, right = false;
        AIScript script("bot");
        while (running) {
            send_moves(&server, up, down, left, right);
            if (playwithbot) {
                int move = script.getNextMove();
                for (int i = 0; i < 20; i++) {
                    server.player_move(static_cast<MoveType>(move));
                    SDL_Delay(5);
                }
                SDL_Delay(1);
            }
            SDL_Event event;

            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN: {
                        SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                left = true;
                                break;
                            case SDLK_RIGHT:
                                right = true;
                                break;
                            case SDLK_UP:
                                up = true;
                                break;
                            case SDLK_DOWN:
                                down = true;
                                break;
                        }
                        break;
                    }
                    case SDL_KEYUP: {
                        SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                left = false;
                                break;
                            case SDLK_RIGHT:
                                right = false;
                                break;
                            case SDLK_UP:
                                up = false;
                                break;
                            case SDLK_DOWN:
                                down = false;
                                break;
                        }
                        break;
                    }
                }
            }
            SDL_Delay(20);
        }

        // stopping all threads
        state_receiver.stop();
        frame_drawer.stop();
        state_receiver.join();
        frame_drawer.join();
    } catch (SDLException &e) {
        std::cout << e.what() << '\n';
    }
}
