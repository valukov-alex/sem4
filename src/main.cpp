#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include "Particle.h"
#include "Basket.h"
#include <cmath>


const float PARTICLES_RADIUS = 5;
const float TIME_QUEUE = 0.2;
const float BALLS_SPEED = 50;

struct Map {
	Vector2 size;
	std::vector<std::vector<Basket>> baskets;
	void update(float dt) {
		/*for (int i = 0; i < particles.size(); i++) {
			Vector2 F;
			for (int j = 0; j < particles.size(); j++)
				if (i != j)
					F += particles[i].Force(particles[j]);
			particles[i].acceleration = F / particles[i].mass;
		}
		for (auto& b : particles) {
			if (b.position.x < 0 || b.position.x > size.x)
				b.velocity.x = -b.velocity.x;
			if (b.position.y < 0 || b.position.y > size.y)
				b.velocity.y = -b.velocity.y;
			b.UpdatePosition(dt);
		}*/
	}

};


int main() {
	Map map;
	std::cin >> map.size;
	sf::RenderWindow window(sf::VideoMode(map.size.x, map.size.y), "My window");
	double preTime = 0;
	sf::Clock clock;
	sf::Texture texture;
	Particle particle;
	particle.mass = 1;
	sf::CircleShape circle;
	circle.setRadius(PARTICLES_RADIUS);
	circle.setFillColor(sf::Color::Blue);
	double t_q = TIME_QUEUE;
	float scale = 1.0f;



	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time time = clock.getElapsedTime();
		double dt = time.asSeconds() - preTime;

		window.clear(sf::Color::White);



		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			t_q += dt;
			if (t_q >= TIME_QUEUE) {
				particle.radius = PARTICLES_RADIUS;
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				particle.position = Vector2(mousePosition.x + particle.radius, mousePosition.y + particle.radius);
				int rnd = rand() % 360;
				Vector2 t(sin(rnd), cos(rnd));
				particle.velocity = t * BALLS_SPEED;
				map.particles.push_back(particle);
				t_q = 0;
			}
		}
		map.update(dt);
		if (!map.particles.empty())
			for (int i = 0; i < map.particles.size(); i++) {
//				std::cout << map.balls[i].velocity << std::endl;
				circle.setPosition(map.particles[i].position.x, map.particles[i].position.y);
				window.draw(circle);
			}
		window.display();

		preTime = time.asSeconds();
	}

	return 0;
}
