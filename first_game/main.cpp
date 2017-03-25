#include <SFML\Graphics.hpp>
#include "Vector2.h"

const float PI = 3.1415;

const float TIME_QUEUE = 0.2;

float x_size, y_size;

struct Hero
{
	Vector2 pos;
	Vector2 velocity;
	float radius;
	Vector2 direction;

	void update(float dt)
	{
		pos += velocity * dt;
	}
};

struct Bullet
{
	Vector2 pos;
	Vector2 velocity;
	float radius;
	Vector2 direction;

	void update(float dt)
	{
		pos += velocity * dt;
	}
};

bool delete_blt(Bullet value)
{
	if (value.pos.x < 0 || value.pos.x > x_size || value.pos.y < 0 || value.pos.y > y_size)
		return true;
	else
		return false;
}

struct Map {
	Vector2 size;
	Hero hero;
	std::vector<Bullet> bullets;
	void update(float dt)
	{
		hero.update(dt);
		for (auto& b : bullets)
			b.update(dt);
		if (hero.pos.x > size.x)
			hero.pos = Vector2(size.x, hero.pos.y);
		if (hero.pos.x < 0)
			hero.pos = Vector2(0, hero.pos.y);
		if (hero.pos.y > size.y)
			hero.pos = Vector2(hero.pos.x, size.y);
		if (hero.pos.y < 0)
			hero.pos = Vector2(hero.pos.x, 0);
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), delete_blt), bullets.end());
//		std::cout << bullets.size() << std::endl;
	}


};


int main()
{
	Map map;
	std::cin >> map.size;
	x_size = map.size.x;
	y_size = map.size.y;
	sf::RenderWindow window(sf::VideoMode(map.size.x, map.size.y), "My window");
	Bullet bullet;
	double preTime = 0;
	sf::Clock clock;
	sf::Texture texture;
	sf::Texture texture_bullet;
	texture.loadFromFile("naruto.png");
	sf::Sprite naruto(texture);
	sf::Vector2f scale = naruto.getScale();
	naruto.setScale(scale.x / 4, scale.y / 4);
	texture_bullet.loadFromFile("rass.png");
	sf::Sprite rass(texture_bullet);
	scale = rass.getScale();
	rass.setScale(scale.x / 7, scale.y / 7);
	sf::Sprite blt;
	double t_q = TIME_QUEUE;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time time = clock.getElapsedTime();
		double dt = time.asSeconds() - preTime;

		window.clear(sf::Color::Red);

		map.hero.velocity = Vector2(0, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			map.hero.velocity += Vector2(-1000, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			map.hero.velocity += Vector2(1000, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			map.hero.velocity += Vector2(0, -1000);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			map.hero.velocity += Vector2(0, 1000);


		sf::Vector2u circleSize = naruto.getTexture()->getSize();
		naruto.setOrigin(circleSize.x / 2, circleSize.y / 2);

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		map.hero.direction = Vector2(mousePosition.x, mousePosition.y) - map.hero.pos;

		naruto.setPosition(map.hero.pos.x, map.hero.pos.y);
		naruto.setRotation(90 + atan2f(map.hero.direction.y, map.hero.direction.x) * 180 / PI);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			t_q += dt;
			if (t_q >= TIME_QUEUE)
			{
				bullet.pos = map.hero.pos;
				bullet.velocity = map.hero.direction.Norm() * 700;
				map.bullets.push_back(bullet);
				t_q = 0;
			}
		}

		if (!map.bullets.empty())
			for (int i = 0; i < map.bullets.size(); i++)
			{
				rass.setPosition(map.bullets[i].pos.x, map.bullets[i].pos.y);
//				blt.setTexture(texture_bullet);
				window.draw(rass);
			}

		map.update(dt);

		window.draw(naruto);
		window.draw(rass);
		window.display();

		preTime = time.asSeconds();
	}

	return 0;
}
