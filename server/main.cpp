#include "server/Server.h"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Wrong params: /server_test service track.txt";
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
			if (input == 'q') return 0;
			else if (input == 'm') server.print_mods();
			else if (isdigit(input)) server.toggle_mod(input - '0');
			else
				continue;
		}
		return 0;
	} catch (...) {
		return 1;
	}
}
