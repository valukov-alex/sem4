#include "Map.h"
#include <algorithm>
#include <cmath>
#include <fstream>

const double BALLS_SPEED = 2500;

double dt1 = 0.0001;

void Map::push_prtcls_into_vessel(int num, float concentration, Particle& obj1) {
	Particle obj = obj1;
	int N_ptcl = (vessels[num].bottom_right.x - vessels[num].top_left.x) *  (vessels[num].bottom_right.y - vessels[num].top_left.y) *  concentration;
	std::cout << num << ") push: " << N_ptcl << std::endl;
	int m_push = sqrt((vessels[num].bottom_right.x - vessels[num].top_left.x) * N_ptcl / (vessels[num].bottom_right.y - vessels[num].top_left.y));
	int n_push = N_ptcl / m_push;
	std::cout << "push: " << m_push*n_push << std::endl;
	std::cout << "n,m push =  " << n_push << " " << m_push << std::endl;
	for(int i_p = 0; i_p < n_push; i_p++)
		for (int j_p = 0; j_p < m_push; j_p++) {
			int rnd = rand() % 360;
			Vector2 t(sin(rnd), cos(rnd));
			obj.velocity = t * BALLS_SPEED;
			obj.position = Vector2(vessels[num].top_left.x + (i_p+1) * (vessels[num].bottom_right.x - vessels[num].top_left.x) / n_push, vessels[num].top_left.y + j_p * (vessels[num].bottom_right.y - vessels[num].top_left.y) / m_push);
			obj.previosPosition = obj.position - obj.velocity * dt1 / 2;
			for (int i = 1; i <= n - 2; i++)		//  цикл по всем
				for (int j = 1; j <= m - 2; j++)	//			корзинам
					if (baskets[i][j].belong(obj))
						baskets[i][j].particles.push_back(obj);
		}
}

double Map::Kinetic() {
	double K = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if (!baskets[i][j].particles.empty()) 
				for (auto it = baskets[i][j].particles.begin(); it != baskets[i][j].particles.end(); it++)
					K += m * pow((*it).velocity.Len(), 2) / 2;
	return K;
}

double Map::Potential() {
	double P = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!baskets[i][j].particles.empty())
				for (auto it = baskets[i][j].particles.begin(); it != baskets[i][j].particles.end(); it++)
					for (int i_neigh = i - 1; i_neigh <= i + 1; i_neigh++)
						for (int j_neigh = j - 1; j_neigh <= j + 1; j_neigh++)
							if (!baskets[i_neigh][j_neigh].particles.empty())
								for (auto it_neigh = baskets[i_neigh][j_neigh].particles.begin(); it_neigh != baskets[i_neigh][j_neigh].particles.end(); it_neigh++)
									if (it_neigh != it && (*it).length(*it_neigh) <= size_basket)
										P += (*it).get_potential(*it_neigh);
	return P;
}

void Map::update_segments() {
	for (auto it = vessels.begin(); it != vessels.end(); it++) {
		std::cout << "left:" << std::endl;
		for (auto it_seg = (*it).left.segments.begin(); it_seg != (*it).left.segments.end(); it_seg++) {
			(*it_seg).pos.x = (*it).top_left.x;
			(*it_seg).pos.y = (*it_seg).start;
			std::cout << "pos = " << (*it_seg).pos << " start, end =" << (*it_seg).start << " " << (*it_seg).end << std::endl;
		}
		std::cout << std::endl;
		std::cout << "right:" << std::endl;
		for (auto it_seg = (*it).right.segments.begin(); it_seg != (*it).right.segments.end(); it_seg++) {
			(*it_seg).pos.x = (*it).bottom_right.x;
			(*it_seg).pos.y = (*it_seg).start;
			std::cout << "pos = " << (*it_seg).pos << " start, end =" << (*it_seg).start << " " << (*it_seg).end << std::endl;
		}
		std::cout << std::endl;
		std::cout << "top:" << std::endl;
		for (auto it_seg = (*it).top.segments.begin(); it_seg != (*it).top.segments.end(); it_seg++) {
			(*it_seg).pos.x = (*it_seg).start;
			(*it_seg).pos.y = (*it).top_left.y;
			std::cout << "pos = " << (*it_seg).pos << " start, end =" << (*it_seg).start << " " << (*it_seg).end << std::endl;
		}
		std::cout << std::endl;
		std::cout << "bot:" << std::endl;
		for (auto it_seg = (*it).bottom.segments.begin(); it_seg != (*it).bottom.segments.end(); it_seg++) {
			(*it_seg).pos.x = (*it_seg).start;
			(*it_seg).pos.y = (*it).bottom_right.y;
			std::cout << "pos = " << (*it_seg).pos << " start, end =" << (*it_seg).start << " " << (*it_seg).end << std::endl;
		}
	}
}

void Map::contact_with_wall(Particle& obj){
	if (obj.position.x  < 0 || (obj.position.x - size.x + 2 * obj.radius) > 0)
		if (obj.velocity.x * (obj.position.x - size.x + 2 * obj.radius) > 0)
			obj.velocity.x = -obj.velocity.x;
	if (obj.position.y < 0 || (obj.position.y - size.y + 2 * obj.radius) > 0)
		if (obj.velocity.y * (obj.position.y - size.y + 2 * obj.radius) > 0)
			obj.velocity.y = -obj.velocity.y;
	for (auto it = vessels.begin(); it != vessels.end(); it++) {
		if ((obj.previosPosition.x - (*it).top_left.x) > 0 && (obj.position.x - (*it).top_left.x) <= 0 && obj.velocity.x < 0 && ((*it).left.have_wall(obj.previosPosition.y) || (*it).left.have_wall(obj.position.y))) {
			obj.velocity.x = -obj.velocity.x;
	//		return;
		}
		if ((obj.previosPosition.x - (*it).bottom_right.x) < 0 && (obj.position.x - (*it).bottom_right.x) >= 0 && obj.velocity.x > 0 && ((*it).right.have_wall(obj.previosPosition.y) || (*it).right.have_wall(obj.position.y))) {
			obj.velocity.x = -obj.velocity.x;
	//		return;
		}
		if ((obj.previosPosition.y - (*it).bottom_right.y) < 0 && (obj.position.y - (*it).bottom_right.y) >= 0 && obj.velocity.y > 0 && ((*it).bottom.have_wall(obj.previosPosition.x) || (*it).bottom.have_wall(obj.position.x))) {
			obj.velocity.y = -obj.velocity.y;
	//		return;
		}
		if ((obj.previosPosition.y - (*it).top_left.y) > 0 && (obj.position.y - (*it).top_left.y) <= 0 && obj.velocity.y < 0 && ((*it).top.have_wall(obj.previosPosition.x) || (*it).top.have_wall(obj.position.x))) {
			obj.velocity.y = -obj.velocity.y;
		//	return;
		}
	}	
}

void Map::push_baskets(double sz) {
	size_basket = sz;
	std::vector<Basket> column_baskets;
	Basket one_basket(sz);
	one_basket.size = Vector2(sz, sz);
	m = size.y / sz + 4;
	n = size.x / sz + 4;
	for (int i = 0; i < n; i++) {
		baskets.push_back(column_baskets);
		for (int j = 0; j < m; j++) {
			one_basket.coord = Vector2(sz * (i - 1.5), sz * (j - 1.5));
			baskets[i].push_back(one_basket);
		}
	}
}

void Map::update(double dt) {

/*	for (int j = 1; j < m - 1; j++)	 //  цикл по всем 
		for (int i = 1; i < n - 1; i++) //			 корзинам
			if (!baskets[i][j].particles.empty()) { //проверяем что корзина[i][j] не пуста
				for (auto it = baskets[i][j].particles.begin(); it != baskets[i][j].particles.end(); it++)
					if (!baskets[i][j].belong(*it)) {
						Particle t = (*it);
						for (int i_neigh = i - 1; i_neigh <= i + 1; i_neigh++)		//цикл по соседям
							for (int j_neigh = j - 1; j_neigh <= j + 1; j_neigh++)	//		и самой себе
								if (baskets[i_neigh][j_neigh].belong(t)) {
									baskets[i_neigh][j_neigh].particles.push_back(t);
									break;
								}
					}
				baskets[i][j].particles.erase(std::remove_if(baskets[i][j].particles.begin(), baskets[i][j].particles.end(), 
					[&](Particle & o) {return !baskets[i][j].belong(o); }), 
						baskets[i][j].particles.end());
			}*/

					
	for (int i = 1; i < n - 1; i++)		//  цикл по всем
		for (int j = 1; j < m - 1; j++)	//			корзинам
			if (!baskets[i][j].particles.empty()) { //проверяем что корзина[i][j] не пуста
				for (auto it = baskets[i][j].particles.begin(); it != baskets[i][j].particles.end(); it++) {
					contact_with_wall(*it);
					Vector2 F(0, 0);
					for (int i_neigh = i - 1; i_neigh <= i + 1; i_neigh++)		//	обходим баскет
						for (int j_neigh = j - 1; j_neigh <= j + 1; j_neigh++) {	//			и все соседние баскеты
							if (!baskets[i_neigh][j_neigh].particles.empty())	//	проверка на пустоту
								for (auto it_neigh = baskets[i_neigh][j_neigh].particles.begin(); it_neigh != baskets[i_neigh][j_neigh].particles.end(); it_neigh++)
									if (it != it_neigh && (*it).length(*it_neigh) <= size_basket)
										F += (*it).Force(*it_neigh);
						}
					(*it).acceleration = F / (*it).mass;
					if (!baskets[i][j].belong(*it)) {
						Particle t = (*it);
						for (int i_neigh = i - 1; i_neigh <= i + 1; i_neigh++)		//цикл по соседям
							for (int j_neigh = j - 1; j_neigh <= j + 1; j_neigh++)	//		и самой себе
								if (baskets[i_neigh][j_neigh].belong(t)) {
									baskets[i_neigh][j_neigh].particles.push_back(t);
									break;
									break;
								}
					}
				}
				baskets[i][j].particles.erase(std::remove_if(baskets[i][j].particles.begin(), baskets[i][j].particles.end(),
					[&](Particle & o) {return !baskets[i][j].belong(o); }),
					baskets[i][j].particles.end());
			}
	for (int i = 1; i < n - 1; i++)		//  цикл по всем
		for (int j = 1; j < m - 1; j++)	//			корзинам
			if (!baskets[i][j].particles.empty()) //проверяем что корзина[i][j] не пуста
				for (auto it = baskets[i][j].particles.begin(); it != baskets[i][j].particles.end(); it++)  //обходим молекулы корзины
					(*it).UpdatePosition(dt);
}

void Map::vessels_from_file(std::string file_name) {
	std::ifstream fin(file_name);
	int n_vessels;
	Vessel vessel;
	fin >> n_vessels;
	for (int i = 0; i < n_vessels; ++i) {
		fin >> vessel.top_left >> vessel.bottom_right;
		vessels.push_back(vessel);
	}
}

void Map::split_sides() {
	for (auto it = vessels.begin(); it != vessels.end(); it++)
		(*it).push_segments();
	for (auto it1 = vessels.begin(); it1 != vessels.end() ; it1++)
		for (auto it2 = vessels.begin(); it2 != vessels.end(); it2++)
			if (it1 != it2) {
				if ((*it1).bottom_right.x == (*it2).top_left.x)
					(*it1).right.common_sides((*it2).left);
				if ((*it1).top_left.x == (*it2).bottom_right.x)
					(*it1).left.common_sides((*it2).right);
				if ((*it1).bottom_right.y == (*it2).top_left.y)
					(*it1).bottom.common_sides((*it2).top);
				if ((*it1).top_left.y == (*it2).bottom_right.y)
					(*it1).right.common_sides((*it2).left);
			}
	for (int i = 0; i < vessels.size(); i++) {
		std::cout << i + 1 << ") top_left = " << vessels[i].top_left << "; bottom_right = " << vessels[i].bottom_right << std::endl;
		std::cout << "left: " << std::endl;
		for (int j = 0; j < vessels[i].left.segments.size(); j++)
			std::cout << "start= " << vessels[i].left.segments[j].start << "; end= " << vessels[i].left.segments[j].end << std::endl;
		std::cout << "top: " << std::endl;
		for (int j = 0; j < vessels[i].top.segments.size(); j++)
			std::cout << "start= " << vessels[i].top.segments[j].start << "; end= " << vessels[i].top.segments[j].end << std::endl;
		std::cout << "right: " << std::endl;
		for (int j = 0; j < vessels[i].right.segments.size(); j++)
			std::cout << "start= " << vessels[i].right.segments[j].start << "; end= " << vessels[i].right.segments[j].end << std::endl;
		std::cout << "bot: " << std::endl;
		for (int j = 0; j < vessels[i].bottom.segments.size(); j++)
			std::cout << "start= " << vessels[i].bottom.segments[j].start << "; end= " << vessels[i].bottom.segments[j].end << std::endl;
		std::cout << std::endl;
	}
}