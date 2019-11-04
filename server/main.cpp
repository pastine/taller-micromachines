#include "server/Server.h"
#include <iostream>

int main(int argc, char* argv[]) {
  char *aux = argv[1];
  std::string service(aux);
  Server server(service);
  server.start();
  while (std::getchar() != 'q') { }
  return 0;
}
