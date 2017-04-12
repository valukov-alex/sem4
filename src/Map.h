#pragma once
#include "Basket.h"

struct Map_Baskets {
	std::vector<std::vector<Basket>> baskets;
	int n, m;
};

struct Map {
	Vector2 size;
	Map_Baskets map_baskets;
	Map_Baskets push_baskets(float sgm);
	void update(float dt);
};
