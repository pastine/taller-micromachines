#include <dlfcn.h>

int main() {
    void *shared_lib = dlopen("./libHelloWorld.so", RTLD_NOW);
    void (*hello)(void);
    *(void **) (&hello) = dlsym(shared_lib, "hello");
    hello();
    return 0;
}
