#include "Particle.h"
#include <cmath>


Particle::Particle() {
	float eps = 10;
	float sgm = 50;
	Vector2 velocity = Vector2(0, 0);
	Vector2 acceleration = Vector2(0, 0);
	float mass = 1;
};

Vector2 Particle::GetImpulse() const {
	Vector2 obj;
	obj = velocity * mass;
	return obj;
}

void Particle::UpdatePosition(float dt) {
	velocity += acceleration * dt;
	position += velocity * dt;
}

Vector2 Particle::Force(Particle& obj) {
	Vector2 F;
	Vector2 d = obj.position - position;
	F = 4 * eps * (6 * pow(sgm, 6) / pow(d.Len(), 7) - 12 * pow(sgm, 12) / pow(d.Len(), 13) ) * d.Norm();
	return F;
}

float Particle::Particle_length(Particle& lhs, Particle& rhs){
	Vector2 t = lhs.position - rhs.position;
	return(t.Len());
}