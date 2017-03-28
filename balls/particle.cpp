#include "particle.h"

MaterialPoint::MaterialPoint()
{
	Vector2 velocity = Vector2(0, 0);
	Vector2 acceleration = Vector2(0, 0);
	float mass = 1;
};

Vector2 MaterialPoint::GetImpulse() const
{
	Vector2 obj;
	obj = velocity * mass;
	return obj;
}

void MaterialPoint::UpdatePosition(float dt)
{
	velocity += acceleration * dt;
	position += velocity * dt;
}