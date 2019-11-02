#include "server/Server.h"

int main(int argc, char* argv[]) {
  char *aux = argv[1];
  std::string service(aux);
  Server server(service);
  server.run();
}
