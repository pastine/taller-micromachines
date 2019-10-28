#include "server/circuit_generator.h"
#include <iostream>
#include <random>
#define H 25
#define W 150

#define NORTH 3
#define SOUTH 21
#define WEST 3
#define EAST 146

#define GRASS 0
#define ROAD 1
#define HEALTH 2
#define BOOST 3
#define STONE 4
#define OIL 5
#define MUD 6
#define FLAG 7
#define PROB 0.2

int modifiers[5] = {HEALTH, BOOST, STONE, OIL, MUD};

int get_surface(double num) {
  if (num > PROB) {
    return ROAD;
  } else {
    return modifiers[rand() % 5];
  }
}

void CircuitGenerator::generate_circuit() {
  int circuit[H][W];
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.01);

  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if((i == NORTH || i == SOUTH) && (j >= WEST && j <= EAST)) {
        double num = dist(mt);
        circuit[i][j] = get_surface(num);
      } else if ((j == WEST || j == EAST) && (i >= NORTH && i <= SOUTH)) {
        double num = dist(mt);
        circuit[i][j] = get_surface(num);
      } else {
        circuit[i][j] = GRASS;
      }
    }
    circuit[NORTH][WEST] = FLAG;
  }

  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
     if(circuit[i][j] == 1) {
      std::cout<<'*';
     } else if(circuit[i][j] == 2) {
        std::cout<<"\033[35mH\033[0m";
     } else if(circuit[i][j] == 3) {
        std::cout<<"\033[35mB\033[0m";;
     } else if(circuit[i][j] == 4) {
        std::cout<<"\033[35mS\033[0m";;
     } else if(circuit[i][j] == 5) {
        std::cout<<"\033[35mO\033[0m";;
     } else if(circuit[i][j] == 6) {
        std::cout<<"\033[35mM\033[0m";;
     } else if(circuit[i][j] == 7) {
       std::cout<< "\033[1;31m&\033[0m";
     } else {
       std::cout<< "\033[32m.\033[0m";
     }
    }
    std::cout<<"\n";
  }

}

//int main() {
//  CircuitGenerator::generate_circuit();
//  return 0;
//}