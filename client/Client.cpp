#include <dirent.h>
#include <QtWidgets/QApplication>
#include <client/Launcher.h>
#include <client/ThStateReceiver.h>
#include <client/ThFrameDrawer.h>
#include <client/AIScript.h>
#include <client/SDLException.h>
#include "client/Client.h"

const int JOYSTICK_DEAD_ZONE = 8000;

Client::Client(std::string &host, std::string &service) : server(host, service) {}

void _send_moves(ServerProxy *server, bool up, bool down, bool left, bool right);

void Client::start() {
    try {
        //Audio audio;
        ThStateReceiver state_receiver(&server, &queue);
        ThFrameDrawer frame_drawer(&queue, map);
        state_receiver.start();
        frame_drawer.start();
        AIScript script(botNames[playwithbot]);

        bool running = true;
        bool up = false, down = false, left = false, right = false;
        SDL_Joystick *gGameController = NULL;
        if (SDL_NumJoysticks() >= 1) {
            gGameController = SDL_JoystickOpen(0);
            std::cout << "Joystick found!" << "\n";
        }
        while (running) {
            _send_moves(&server, up, down, left, right);

            if (playwithbot > 0) {
                int move = script.getNextMove();
                for (int i = 0; i < 20; i++) {
                    server.player_move(static_cast<MoveType>(move));
                    SDL_Delay(20);
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
                            case SDLK_a:
                                left = true;
                                break;
                            case SDLK_RIGHT:
                            case SDLK_d:
                                right = true;
                                break;
                            case SDLK_UP:
                            case SDLK_w:
                                up = true;
                                break;
                            case SDLK_DOWN:
                            case SDLK_s:
                                down = true;
                                break;
                        }
                        break;
                    }
                    case SDL_KEYUP: {
                        SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                            case SDLK_a:
                                left = false;
                                break;
                            case SDLK_RIGHT:
                            case SDLK_d:
                                right = false;
                                break;
                            case SDLK_UP:
                            case SDLK_w:
                                up = false;
                                break;
                            case SDLK_DOWN:
                            case SDLK_s:
                                down = false;
                                break;
                        }
                        break;
                    }
                    case SDL_JOYAXISMOTION: {
                        if (event.jaxis.which == 0) {
                            if (event.jaxis.axis == 0) {
                                if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                                    left = true;
                                } else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) {
                                    right = true;
                                } else {
                                    left = false;
                                    right = false;
                                }
                            }
                            if (event.jaxis.axis == 1) {
                                if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                                    up = true;
                                } else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) {
                                    down = true;
                                } else {
                                    up = false;
                                    down = false;
                                }
                            }
                        }
                    }
                }
            }
            SDL_Delay(20);
        }
        state_receiver.stop();
        frame_drawer.stop();
        state_receiver.join();
        frame_drawer.join();
        SDL_JoystickClose(gGameController);
    } catch (SocketException &e) {
        std::string err_msg = "Error in Client::start -> ";
        err_msg += e.what();
        throw std::runtime_error(err_msg);
    } catch (std::runtime_error &e) {
        std::string err_msg = "Error in Client::start -> ";
        err_msg += e.what();
        throw std::runtime_error(err_msg);
    }
}

std::map<int, std::string> _get_bot_names();

void Client::handshake(int argc, char** argv) {
    std::map<std::string, int> races_ids_players = server.handshake();
    int retValue = -1;
    playwithbot = -1;
    std::string playerName = "Player";
    botNames = _get_bot_names();
    QApplication app(argc, argv);
    Launcher launcher(races_ids_players, botNames, &retValue, &playwithbot, &playerName);
    launcher.show();
    app.exec();
    map = server.handshake_answer(retValue, playerName);
}

std::map<int, std::string> _get_bot_names() {
    DIR* botDir = opendir("client/bots");
    if (!botDir) return {};
    struct dirent *ent;
    std::map<int, std::string> names;
    int counter = 1;
    while ((ent = readdir(botDir)) != NULL) {
        std::string name = ent->d_name;
        if (name == "." || name == "..") continue;
        names.insert({counter++, name});
    }
    closedir(botDir);
    return names;
}

void _send_moves(ServerProxy *server, bool up, bool down, bool left, bool right) {
    if (left && up) server->player_move(MoveType::UPLEFT);
    else if (right && up) server->player_move(MoveType::UPRIGHT);
    else if (left && down) server->player_move(MoveType::DOWNLEFT);
    else if (right && down) server->player_move(MoveType::DOWNRIGHT);
    else if (up) server->player_move(MoveType::UP);
    else if (down) server->player_move(MoveType::DOWN);
    else if (right) server->player_move(MoveType::RIGHT);
    else if (left) server->player_move(MoveType::LEFT);
}
