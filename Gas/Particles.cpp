#include "Particle.h"
#include <cmath>


Particle::Particle() {
	std::cout << "kostr" << std::endl;
	double eps = 8;
	double sgm = 9.0;
	Vector2 velocity = Vector2(0, 0);
	Vector2 acceleration = Vector2(0, 0);
	double mass = 1;
}

Vector2 Particle::GetImpulse() const {
	Vector2 obj;
	obj = velocity * mass;
	return obj;
}

void Particle::UpdatePosition(double dt) {
	previosPosition = position;
	velocity += acceleration * dt;
	position += velocity * dt;
//	std::cout << acceleration << std::endl;
//	std::cout << position << std::endl;
//	std::cout << previosPosition << std::endl;
//	position = position * 2 - previosPosition + acceleration* dt * dt;
//	previosPosition = t;
//	std::cout << position << std::endl;
//	std::cout << previosPosition << std::endl << std::endl;
}

Vector2 Particle::Force(Particle& obj) {
	Vector2 F;
	Vector2 d = obj.position - position;
	F = 4 * eps * (6 * pow(sgm, 6) / pow(d.Len(), 7) - 7 * pow(sgm, 7) / pow(d.Len(), 7) ) * d.Norm();
	return F;
}


double Particle::length(Particle& obj){
	Vector2 d = position - obj.position;
	return(d.Len());
}

double Particle::get_potential(Particle& obj) {
	Vector2 d = position - obj.position;
	double U = 4 * eps * ( pow(sgm / d.Len(), 6) - pow(sgm / d.Len(), 12) );
	return U;
}

Particle& Particle::operator=(const Particle& obj) {
	if (this == &obj)
		return *this;
	mass = obj.mass;
	radius = obj.radius;
	eps = obj.eps;
	sgm = obj.sgm;
	clr = obj.clr;
	position = obj.position;
	velocity = obj.velocity;
	acceleration = obj.acceleration;
}