//
// Created by casimiro on 30/10/19.
//

#ifndef TALLER_MICROMACHINES_CLIENTACCEPTER_H
#define TALLER_MICROMACHINES_CLIENTACCEPTER_H


#include <common/Socket.h>
#include "ClientProxy.h"
#include <string>

class ClientAccepter {
public:
    explicit ClientAccepter(std::string &service);

    ClientProxy accept_client();

    void shutdown();

private:
    Socket acc_socket;
};


#endif //TALLER_MICROMACHINES_CLIENTACCEPTER_H
