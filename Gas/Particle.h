#pragma once
#include <SFML\Graphics.hpp>
#include "Vector2.h"

class Particle {
public:
	Particle();

	double mass;
	double radius;
	double eps;
	double sgm;
	int vessel_belong;
	sf::Color clr;

	Particle& operator=(const Particle& obj);
	double length(Particle& rhs);
	void UpdatePosition(double dt);
	Vector2 Force(Particle& obj);
	Vector2 GetImpulse() const;
	double get_potential(Particle& obj);
	Vector2 position;
	Vector2 previosPosition;
	Vector2 velocity;
	Vector2 acceleration;
};
