#include "server/ClientAccepter.h"

ClientAccepter::ClientAccepter(std::string &service) {
    this->acc_socket.bind_and_listen(service);
}

ClientProxy ClientAccepter::accept_client() {
    Communication comm(this->acc_socket.accept_connection());
    ClientProxy client(std::move(comm));

    // this won't be copied as copy operations for client
    // were deleted
    return client;
}

void ClientAccepter::shutdown() {
    this->acc_socket.shutdown();
}

