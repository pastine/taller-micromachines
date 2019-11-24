#ifndef TALLER_MICROMACHINES_SERVER_H
#define TALLER_MICROMACHINES_SERVER_H

#include "ClientAccepter.h"
#include "Race.h"
#include <common/Thread.h>
#include <string>
#include <list>
#include <map>

class Server : public Thread {
private:
    ClientAccepter acceptor;
    std::list<Race *> races;
    bool running = true;
    char* track_file;

public:
    explicit Server(std::string &service, char* file);

    virtual void run();

    virtual void stop();

    ~Server();

    void reaper();

    void create_race(ClientProxy &proxy, std::string name);

    void add_player_to_race(ClientProxy &new_client, int id, std::string name);

    int handshake_get_race(ClientProxy &new_client);

    void print_mods();

    void toggle_mod(int i);

    void load_mods();

    std::map<int, std::string> mods;
};


#endif //TALLER_MICROMACHINES_SERVER_H
