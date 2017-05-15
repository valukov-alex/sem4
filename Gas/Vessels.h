#pragma once
#include "Vector2.h"
#include <vector>
#include <String>
#include "Particle.h"

struct Segment {
	Vector2 pos;
	double start;
	double end;
	std::string crossing(Segment& obj);
	bool point_inside(double pos);
};

struct Side {
	std::vector<Segment> segments;
	void common_sides(Side& obj);
	bool have_wall(float pos);
};

struct Vessel {
	Side left;
	Side right;
	Side bottom;
	Side top;
	Vector2 top_left;
	Vector2 bottom_right;
	bool belong(Particle& obj);
	void push_segments();
};
