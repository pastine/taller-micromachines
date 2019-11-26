#include <SDL2/SDL.h>
#include <iostream>
#include <QtWidgets/QApplication>
#include "client/SDLException.h"
#include "client/Launcher.h"
#include "client/Client.h"


bool _validate_params(int argc, char **argv) {
    std::string expected_format = "Expected format: ./client <host> <service/port>\n";
    if (argc != 3) {
        std::cout << "Invalid number of parameters.\n";
        std::cout << expected_format;
        return false;
    }
    return true;
}

int main(int argc, char **argv) {
    try {
        if (!_validate_params(argc, argv)) return 1;

        std::string host(argv[1]);
        std::string service(argv[2]);

        Client client(host, service);
        client.handshake(argc, argv);
        client.start();
        return 0;
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    } catch (std::runtime_error &e) {
        std::cout << e.what() << '\n';
    } catch (...) {
        std::cout << "unexpected error occurred :(\n";
    }
}


