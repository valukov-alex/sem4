#include "Basket.h"

Basket::Basket(double sz) {
	Vector2 size(sz, sz);
}

bool Basket::belong(Particle& obj) {
	if (obj.position.x >= coord.x && obj.position.x < coord.x + size.x && obj.position.y >= coord.y && obj.position.y < coord.y + size.y)
		return true;
	else
		return false;
}