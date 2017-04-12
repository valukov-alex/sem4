#pragma once
#include "Particle.h"
#include <vector>

struct Basket {
	Basket();
	Basket(float sgm);

	Vector2 size;
	Vector2 coord;
	std::vector<Particle> particles;

	void push_particle(Particle& obj);
	Particle pop_particle(std::vector<Particle>::iterator it);
	bool belong(Particle& obj);
};
