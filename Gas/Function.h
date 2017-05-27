#pragma once
#include <SFML\Graphics.hpp>
#include "Vessels.h"
#include "Map.h"

struct Point {
	double t;
	double cons;
};

class Function {
public:
	Map *my_map;
	std::vector<Point> points;
	int vessel_num;
	double Volume;
	double value;
	sf::Color color;
	sf::RenderWindow *func_window;

	void start_function(int num_vsl, Map* map, sf::Color clr, sf::RenderWindow *wndw);
	void add_a_point();

};