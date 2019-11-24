
#include <dlfcn.h>
#include "server/Mod.h"

void Mod::modify_state(State &state) {
    void (*middleman)(char *);
    *(void **) (&middleman) = dlsym(shared_lib, "middleman");
    std::string msg = state.json.dump();
    char *new_msg = strdup(msg.c_str());
    middleman(new_msg);
    state = State(new_msg);
    free(new_msg);
}


Mod::Mod(std::string fileName) {
    size_t extIndex = fileName.find_last_of(".");
    std::string libName = fileName.substr(0, extIndex) + ".so";
    shared_lib = dlopen(libName.c_str(), RTLD_NOW);
}

Mod::~Mod() {
    dlclose(shared_lib);
}
