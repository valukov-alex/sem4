#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include "particle.h"

const float BALLS_RADIUS = 25;
const float TIME_QUEUE = 0.2;
const float BALLS_SPEED = 200;

struct Map {
	Vector2 size;
	std::vector<Ball> balls;
	void update(float dt)
	{
		for(int i = 0; i < balls.size(); i++)
			for(int j = i; j < balls.size(); j++)
				if (i != j)
				{
					Vector2 d = balls[j].position - balls[i].position;
					if(d.Len() <= balls[i].radius + balls[j].radius)
						if ((balls[j].velocity - balls[i].velocity) * d <= 0) {
							Vector2 n = d.Norm();
//							std::cout << "n:" << n.Len() << std::endl;
							Vector2 dlt_p = (2 * ((balls[j].velocity - balls[i].velocity) * balls[i].mass * balls[j].mass / (balls[i].mass + balls[j].mass)) * n) * n;
							balls[j].velocity -= dlt_p / balls[j].mass;
							balls[i].velocity += dlt_p / balls[i].mass;
						}

				}
		for (auto& b : balls)
		{
			if (b.position.x < 0 || b.position.x > size.x)
				b.velocity.x = -b.velocity.x;
			if (b.position.y < 0 || b.position.y > size.y)
				b.velocity.y = -b.velocity.y;
			b.UpdatePosition(dt);
		}
	}

};


int main()
{
	Map map;
	std::cin >> map.size;
	sf::RenderWindow window(sf::VideoMode(map.size.x, map.size.y), "My window");
	double preTime = 0;
	sf::Clock clock;
	sf::Texture texture;
	texture.loadFromFile("ball.png");
	Ball ball;
	ball.mass = 1;
	sf::Sprite circle(texture);
	double t_q = TIME_QUEUE;


	float scale = 1.0f;
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

		window.clear(sf::Color::Black);



		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			t_q += dt;
			if (t_q >= TIME_QUEUE)
			{
				ball.radius = BALLS_RADIUS;
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				ball.position = Vector2(mousePosition.x + ball.radius, mousePosition.y + ball.radius);
				int rnd = rand() % 360;
				Vector2 t(sin(rnd), cos(rnd));
				ball.velocity = t * BALLS_SPEED;
				map.balls.push_back(ball);
				t_q = 0;
			}
		}
		map.update(dt);
		if (!map.balls.empty())
			for (int i = 0; i < map.balls.size(); i++)
			{
//				std::cout << map.balls[i].velocity << std::endl;
				circle.setPosition(map.balls[i].position.x, map.balls[i].position.y);
				window.draw(circle);
			}
		window.display();

		preTime = time.asSeconds();
	}

	return 0;
}
