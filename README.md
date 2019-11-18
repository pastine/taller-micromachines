# Taller-MicroMachines

1. Install the dependencies: `./dependencies.sh`
2. Create a `build` directory: `mkdir build && cd build`
3. Compile the project: `cmake ..`
4. Compile any of the different binaries: `make server_test && make client_test`

6. Open (at least) two terminals **on the root directory, not build**:
* On one, run `./server_test 7777`
* On the rest, run `./client_test localhost 7777`
