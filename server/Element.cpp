#include "server/Element.h"
#include <random>
#include <server/Boost.h>
#include <server/Health.h>
#include <server/Oil.h>
#include <server/Mud.h>
#include <server/Stone.h>

void Element::get_element(b2World& world) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.01);
  double num = dist(mt);
  if (num > 0 && num <= 0.20) {
    //return new Boost(world);
  } else if (num > 0.20 && num <= 0.40) {
    //return new Health(world);
  } else if (num > 0.40 && num <= 0.60) {
    //return new Oil(world);
  } else if (num > 0.60 && num <= 0.80) {
    //return new Mud(world);
  } else {
    //return new Stone(world);
  }
}
