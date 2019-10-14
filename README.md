# Taller-MicroMachines

1. Install the dependencies: `./dependencies.sh`
2. Create a `build` directory: `mkdir build && cd build`
3. Compile the project: `cmake ..`
4. Compile any of the different binaries: `make binary`
5. Run the binary: `./binary` 

## Server

### Mods

## Client

### Scripts

The game, from the client side, implements AI-bots, to compete with the user car. This bots are implented as [Lua](https://www.lua.org) scripts, and the binding between the C++ code (the game) and the Lua scripts (the AI) is powered by [LuaBridge](https://github.com/vinniefalco/LuaBridge). [This](https://eliasdaler.wordpress.com/2014/07/18/using-lua-with-cpp-luabridge/) tutorial gives an overview of what can be done with the LuaBridge library.
