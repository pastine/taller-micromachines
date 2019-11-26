#include "server/Server.h"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 3) {
        std::cout << "Wrong params: ./server service track.txt\n";
		return 1;
	}
	try {
		char *aux = argv[1];
		std::string service(aux);
		char *track = argv[2];
		Server server(service, track);
		server.start();
		char input;
		while ((input = std::getchar())) {
            if (input == 'q') break;
            else if (input == 'm') server.print_mods();
            else if (isdigit(input)) server.toggle_mod(input - '0');
            else
                continue;
		}
        std::cout << "Goodbye!\n";
        return 0;
	} catch (...) {
		return 1;
	}
}
