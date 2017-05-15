#include "Vessels.h"

std::string Segment::crossing(Segment& obj) {
	if (obj.start >= end || obj.end <= start)
		return "excluded";
	else
		if (obj.end >= end && obj.start > start)
			return "crossing_end";
		else
			if (obj.start < start && obj.end <= end)
				return "crossing_start";
			else
				if (obj.start < start && obj.end > end)
					return "contains";
				else
					if (obj.start >= start && obj.end <= end)
						return "included";
}

bool Segment::point_inside(double pos) {
	if (pos >= start && pos <= end)
		return true;
	else
		return false;
}


void Vessel::push_segments() {
	Segment segment;
	segment.start = top_left.x;
	segment.end = bottom_right.x;
	top.segments.push_back(segment);
	bottom.segments.push_back(segment);
	segment.start = top_left.y;
	segment.end = bottom_right.y;
	left.segments.push_back(segment);
	right.segments.push_back(segment);
}

bool Side::have_wall(float pos) {
	for (auto it = segments.begin(); it != segments.end(); it++)
		if ((*it).point_inside(pos))
			return true;
	return false;
}

void Side::common_sides(Side& obj){
	std::vector<Segment> buff;
	Segment segment;
	for (auto it = segments.begin(); it != segments.end(); it++)
		for (auto it_obj = obj.segments.begin(); it_obj != obj.segments.end(); it_obj++)
			if ((*it).crossing(*it_obj) == "contains") {
				segment.start = (*it).end;
				segment.end = (*it_obj).end;
				(*it_obj).end = (*it).start;
				segments.erase(it);
				obj.segments.push_back(segment);
				return;
			}
			else
				if ((*it).crossing(*it_obj) == "included") {
					segment.start = (*it_obj).end;
					segment.end = (*it).end;
					(*it).end = (*it_obj).start;
					segments.push_back(segment);
					obj.segments.erase(it_obj);
					return;
				}
				else
					if ((*it).crossing(*it_obj) == "crossing_end") {
						double t = (*it).end;
						(*it).end = (*it_obj).start;
						(*it_obj).start = t;
						return;
					}
					else
						if ((*it).crossing(*it_obj) == "crossing_start") {
							double t = (*it).start;
							(*it).start = (*it_obj).end;
							(*it_obj).end = t;
							return;
						}
}

bool Vessel::belong(Particle& obj) {
	if (obj.position.x >= top_left.x && obj.position.x < bottom_right.x && obj.position.y >= top_left.y && obj.position.y < bottom_right.y)
		return true;
	else
		return false;
}

