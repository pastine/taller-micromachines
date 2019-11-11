#include "server/Element.h"
#include <random>
#include <server/Boost.h>
#include <server/Health.h>
#include <server/Oil.h>
#include <server/Mud.h>
#include <server/Stone.h>
#include <iostream>


Element* Element::get_element(b2World& world) {
	//TODO method that randomizes position
	float x = 0.0f;
	float y = 0.0f;
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.01);
  double num = dist(mt);
  /*if (num > 0 && num <= 0.20) {
  	std::cout<<"new Boost\n";
    //return new Boost(world);
  } else if (num > 0.20 && num <= 0.40) {
		std::cout<<"new Health\n";
    //return new Health(world);
  }*/
  if (num > 0.40 && num <= 0.60) {
		std::cout<<"new Oil\n";
    return new Oil(world, x, y);
  } else if (num > 0.60 && num <= 0.80) {
		std::cout<<"new Mud\n";
    return new Mud(world, x, y);
  } else {
		std::cout<<"new Stone\n";
    return new Stone(world, x, y);
  }
}
