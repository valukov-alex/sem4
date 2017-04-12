#pragma once
#include "Vector2.h"

class Particle {
public:
	Particle();

	float mass;
	float radius;
	float eps;
	float sgm;

	float Particle_length(Particle& lhs, Particle& rhs);
	void UpdatePosition(float dt);
	Vector2 Force(Particle& rhs);
	Vector2 GetImpulse() const;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
};
