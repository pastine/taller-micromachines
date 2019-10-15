#include <iostream>

extern "C" {
void hello() {
    std::cout << "Hello World, from a cpp shared library!";
}
}
