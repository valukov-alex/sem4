#pragma once
#include "Basket.h"
#include "Vessels.h"

struct Map {
	Vector2 size;
	std::vector<Vessel> vessels;
	std::vector<std::vector<Basket>> baskets;
	std::vector<Segment> seg_verticl;
	std::vector<Segment> seg_horiz;
	int n, m;
	double TIME;
	double size_basket;
	double Potential();
	double Kinetic();
	void push_baskets(double sgm);
	void update(double dt);
	void vessels_from_file(std::string file_name);
	void split_sides();
	void contact_with_wall(Particle& obj);
	void update_segments();
	void push_prtcls_into_vessel(int num, float concentration, Particle& obj);
	double get_concetration(sf::Color clr, int n_ves);
};
