#include "Basket.h"

Basket::Basket() {
	Vector2 size;
}


Basket::Basket(float sz) {
	Vector2 size(sz, sz);
}

void Basket::push_particle(Particle& obj) {
	particles.push_back(obj);
}

Particle Basket::pop_particle(std::vector<Particle>::iterator it) {
	Particle t = *it;
	particles.erase(it);
	return t;
}

bool Basket::belong(Particle& obj) {
	if (obj.position.x > coord.x && obj.position.x < coord.x + size.x && obj.position.y > coord.y && obj.position.y < coord.y + size.y)
		return true;
	else
		return false;
}