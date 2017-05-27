#include "Function.h"


void Function::start_function(int num_vsl, Map* map, sf::Color clr, sf::RenderWindow *wndw) {
	func_window = wndw;
	color = clr;
	vessel_num = num_vsl;
	my_map = map;
	Vector2 diag = map->vessels[vessel_num].bottom_right - map->vessels[vessel_num].top_left;
	Volume = diag.Len();
}

void Function::add_a_point() {
	Point point;
	point.cons = my_map->get_concetration(color, vessel_num);
	point.t = my_map->TIME * 100;
	std::cout << "t,cons = " << point.t << ", " << point.cons << std::endl;
	points.push_back(point);
	std::cout << "points = " << points.size() << std::endl;
}