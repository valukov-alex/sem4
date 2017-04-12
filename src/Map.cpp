#include "Map.h"

Map_Baskets Map::push_baskets(float sz) {
	Map_Baskets t;
	std::vector<Basket> basket;
	Basket b(sz);
	t.m = size.y / sz + 3;
	t.n = size.x / sz + 3;
	for (int i = 0; i < t.n; i++) {
		t.baskets.push_back(basket);
		for (int j = 0; j < t.m; j++) {
			b.coord = Vector2(sz * (i - 1), sz * (j - 1));
			t.baskets[i].push_back(b);
		}
	}
	return t;
}

void Map::update(float dt) {
	for (int j = 1; j < map_baskets.n - 2; j++)
		if (!map_baskets.baskets[1][j].particles.empty())
			for (auto it = map_baskets.baskets[1][j].particles.begin(); it != map_baskets.baskets[1][j].particles.end(); it++) {

			}

}