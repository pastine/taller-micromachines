#include "server/Server.h"
#include <iostream>

int main(int argc, char *argv[]) {
		if (argc != 3) { return 1;}
    char* aux = argv[1];
    std::string service(aux);
    char* track = argv[2];
    Server server(service, track);
    server.start();
    while (std::getchar() != 'q') {}
    return 0;
}
