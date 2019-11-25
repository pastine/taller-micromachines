#include <SDL2/SDL.h>
#include <iostream>
#include <QtWidgets/QApplication>
#include "client/SDLException.h"
#include "client/Launcher.h"
#include "Client.h"





int main(int argc, char **argv) {
    try {
        std::string host(argv[1]);
        std::string service(argv[2]);
        Client client(host, service);
        client.handshake(argc, argv);
        client.start();
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}


