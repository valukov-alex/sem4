#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include "Particle.h"
#include "Basket.h"
#include <cmath>
#include "Map.h"
#include "Function.h"
#include <thread>

const double PARTICLES_RADIUS = 2;
const double TIME_QUEUE = 0.5;
const double BALLS_SPEED = 8000;
const double TIME_SHOW = 0.2;
const double FUNC_UPDATE_TIME = 0.02;
const double DIV_TIME = 0.0001;

int main() {

	std::cout.setf(std::ios_base::fixed);
	std::cout.setf(std::ios::showpoint);
//	std::cout.precision(2);

	Map map;
	map.TIME = 0;
	std::cin >> map.size;
	map.vessels_from_file("vessels.txt");
	map.split_sides();
	map.update_segments();

	std::cout << "horizontal:" << std::endl;
	for (auto it = map.seg_horiz.begin(); it != map.seg_horiz.end(); it++)
		std::cout << "pos = " << (*it).pos << " start, end = " << (*it).start << " " << (*it).end << std::endl;
	std::cout << "vertical:" << std::endl;
	for (auto it = map.seg_verticl.begin(); it != map.seg_verticl.end(); it++)
		std::cout << "pos = " << (*it).pos << " start, end = " << (*it).start << " " << (*it).end << std::endl;

//	sf::RenderWindow window1(sf::VideoMode(1700, 800), "My window");
//	window1.setActive(false);

	sf::RenderWindow window(sf::VideoMode(map.size.x, map.size.y), "My window");
	
	double preTime = 0;
	sf::Clock clock;
	sf::Texture texture;

	Particle particle;
	particle.radius = PARTICLES_RADIUS;
	particle.sgm = 15;
	particle.eps = 100;
	particle.mass = 1;

	sf::CircleShape circle;
	circle.setRadius(PARTICLES_RADIUS);
	circle.setFillColor(sf::Color::Blue);

	double t_q = TIME_QUEUE;
	double scale = 1.0f;
	double t_q1 = 0, t_q2 = 0;
	double dt1 = 0.0001;

	map.push_baskets(2.5*particle.sgm);
	
	particle.clr = sf::Color::Green;
	map.push_prtcls_into_vessel(0, 0.0008, particle);

	particle.clr = sf::Color::Red;
	map.push_prtcls_into_vessel(3, 0.0008, particle);

	double K = map.Kinetic();
	double P = map.Potential();
	std::cout << "start:" << std::endl << "K = " << K << "; P = " << P << "; K + P = " << K + P << std::endl;

	Function func1, func2;
//	func1.start_function(0, &map, sf::Color::Blue, &window1);
//	func2.start_function(2, &map, sf::Color::Red);

//	window1.setActive(false);
	//sf::Thread func1_thread(&rendThread, func1);
	//func1_thread.launch();
//	func1_thread.join();
//	func1_thread.detach();

	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed)
				window.close();
		}

/*		sf::Event event1;
		while (window1.pollEvent(event1)) {
			if (event1.type == sf::Event::Closed)
				window1.close();
		}*/

		sf::Time time = clock.getElapsedTime();
		double dt = time.asSeconds() - preTime;

		window.clear(sf::Color::Black);
		//window1.clear(sf::Color::White);

		for (auto it = map.vessels.begin(); it != map.vessels.end(); it++) {
			sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color::White);
			rectangle.setPosition((*it).top_left.x, (*it).top_left.y);
			rectangle.setSize(sf::Vector2f((*it).bottom_right.x - (*it).top_left.x + 2 * particle.radius, (*it).bottom_right.y - (*it).top_left.y + 2 * particle.radius));
			window.draw(rectangle);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			t_q += dt;
			if (t_q >= TIME_QUEUE) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				particle.position = Vector2(mousePosition.x + particle.radius, mousePosition.y + particle.radius);
				int rnd = rand() % 360;
				Vector2 t(sin(rnd), cos(rnd));
				particle.velocity = t * BALLS_SPEED * 10;
				particle.previosPosition = particle.position - particle.velocity * dt1 / 2;
				particle.clr = sf::Color::Green;
				for (int i = 1; i <= map.n - 2; i++)		//  цикл по всем
					for (int j = 1; j <= map.m - 2; j++)	//			корзинам
						if (map.baskets[i][j].belong(particle)) 
							map.baskets[i][j].particles.push_back(particle);
				t_q = 0;
			}
		}

//		mutex.lock();
		map.update(DIV_TIME);
//		mutex.unlock();

//		func2.update(dt1);
		int n = 0;
		for (int i = 0; i <= map.n - 1; i++)		
			for (int j = 0; j <= map.m - 1; j++)	
				if (!map.baskets[i][j].particles.empty()) 
					for (auto it = map.baskets[i][j].particles.begin(); it != map.baskets[i][j].particles.end(); it++){  
						circle.setPosition((*it).position.x, (*it).position.y);
						circle.setFillColor((*it).clr);
						window.draw(circle);
						n++;
					}
		
		if (t_q1 >= TIME_SHOW) {
//			std::cout << &window1 << std::endl;
			double K = map.Kinetic();
			double P = map.Potential();
			std::cout << "n = " << n << "; K = " << K << "; P = " << P << "; K + P = " << K + P << std::endl;
			t_q1 = 0;
		}
		t_q1 += dt1;
		t_q2 += dt1;
		window.display();

		preTime = time.asSeconds();
	}

//	func1_thread.join();
	return 0;
}
