//
// Created by casimiro on 25/11/19.
//

#ifndef TALLER_MICROMACHINES_CLIENT_H
#define TALLER_MICROMACHINES_CLIENT_H


#include <string>
#include <client/ServerProxy.h>
#include <common/ProtectedQueue.h>
#include <map>

class Client {
public:
    Client(std::string& host, std::string& service);
    void start();
    void handshake(int argc, char** argv);

private:
    ServerProxy server;
    ProtectedQueue<JSON> queue;
    JSON map;
    int playwithbot;
    std::map<int, std::string> botNames;
};


#endif //TALLER_MICROMACHINES_CLIENT_H
