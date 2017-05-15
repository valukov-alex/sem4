#pragma once
#include "Particle.h"
#include <vector>

struct Basket {
	Basket(double sgm);

	Vector2 size;
	Vector2 coord;
	std::vector<Particle> particles;
	bool belong(Particle& obj);
};
