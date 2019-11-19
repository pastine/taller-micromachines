#include "server/Element.h"
#include <random>
#include <vector>


std::vector<float> Element::get_random_pos() {
    std::vector<float> ground = {0.0, 0.0, 34.5, 2.75};
    std::vector<float> ceiling = {0.0, 74.5, 34.5, 2.75};
    std::vector<float> left = {-37.25, 37.25, 2.75, 34.5};
    std::vector<float> right = {37.25, 37.25, 2.75, 34.5};
    std::vector<std::vector<float>> total = {ground, ceiling, left, right};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 3.99);
    int num = dist(mt);

    float x = total[num][0];
    float y = total[num][1];
    float delta_x = total[num][2];
    float delta_y = total[num][3];

    std::random_device rd_1;
    std::mt19937 mt_1(rd_1());
    std::uniform_real_distribution<double> dist_1(x - delta_x, x + delta_x);
    float x_pos = dist_1(mt_1);

    std::random_device rd_2;
    std::mt19937 mt_2(rd_2());
    std::uniform_real_distribution<double> dist_2(y - delta_y, y + delta_y);
    float y_pos = dist_2(mt_2);

    return std::vector<float>{x_pos, y_pos};
}

//Element* Element::get_element(b2World& world) {
//	std::vector<float> pos = get_random_pos();
//	float x = pos[0];
//	float y = pos[1];
//  std::random_device rd;
//  std::mt19937 mt(rd());
//  std::uniform_real_distribution<double> dist(0.0, 1.01);
//  double num = dist(mt);
//	if (num > 0 && num <= 0.20) {
//		std::cout<<"new Boost\n";
//		return new Boost(world, x, y);
//	} else if (num > 0.20 && num <= 0.40) {
//		std::cout<<"new Health\n";
//    return new Health(world, x, y);
//  } else if (num > 0.40 && num <= 0.60) {
//		std::cout<<"new Oil\n";
//    return new Oil(world, x, y);
//  } else if (num > 0.60 && num <= 0.80) {
//		std::cout<<"new Mud\n";
//    return new Mud(world, x, y);
//  } else {
//		std::cout<<"new Boulder\n";
//    return new Boulder(world, x, y);
//  }
//}
