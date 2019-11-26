# Taller-MicroMachines

1. Install the dependencies: `./dependencies.sh`
2. Create a `build` directory: `mkdir build && cd build`
3. Compile the project: `cmake ..`
4. Compile any of the different binaries: `make server && make client`

6. Open (at least) two terminals **on the root directory, not build**:
* On one, run `./server 7777 track.txt`
* On the rest, run `./client localhost 7777`
