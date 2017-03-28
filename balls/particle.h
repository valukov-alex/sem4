#pragma once
#include "Vector2.h"

class MaterialPoint
{
public:
	MaterialPoint();

	void UpdatePosition(float dt);

	Vector2 GetImpulse() const;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	float mass;
};

class Ball : public MaterialPoint
{
public:
	float radius;
	int type;
};