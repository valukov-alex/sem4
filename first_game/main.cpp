#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
	
const int K = 15;
const int IterationCount = 20;

using Centroids = std::vector<sf::Color>;
using ClosestCentroidIndies = std::vector<int>;

sf::Color clr;

struct ColorBuf
{
	int r, b, g, a;
	int count;
	ColorBuf() {
		r = 0;
		b = 0;
		g = 0;
		a = 0;
		count = 0;
	}
	ColorBuf& operator+=(const sf::Color& obj)
	{
		r += obj.r;
		b += obj.b;
		g += obj.g;
		a += obj.a;
		count++;
		return (*this);
	};
	void normalize()
	{
		r = r / count;
		b = b / count;
		g = g / count;
		a = a / count;
		count = 1;
	};
};


float distance(const sf::Color lhs, const sf::Color rhs)
{
	return sqrt(pow(lhs.r - rhs.r, 2) + pow(lhs.g - rhs.g, 2) + pow(lhs.b - rhs.b, 2));
}

Centroids initializeCentroids(const sf::Image& img, int k_)
{
	sf::Color pixel;
	Centroids cntrds;
	for (int i = 0; i < k_; ++i)
	{
		cntrds.push_back(clr);
		pixel = img.getPixel(rand() % img.getSize().x, rand() % img.getSize().y);
		cntrds[i] = pixel;
	}
	std::cout << std::endl;
	return cntrds;
}

ClosestCentroidIndies findClosestCentroids(const sf::Image& img, const Centroids& cntrds)
{
	sf::Color pixel;
	int w = img.getSize().x;
	int h = img.getSize().y;
	ClosestCentroidIndies ids(w*h);
	for (int i = 0; i < ids.size(); ++i)
	{
		int h_pixel = i / w;
		int w_pixel = i - h_pixel * w;
		float max = 100000;
		pixel = img.getPixel(w_pixel, h_pixel);
		for (int j = 0; j < cntrds.size(); ++j) 
		{
			float ds = distance(pixel, cntrds[j]);
			if (ds < max)
			{
				max = ds;
				ids[i] = j;
			}
		}
	}
	return ids;
}

Centroids computeMeans(const sf::Image& img, const ClosestCentroidIndies&  ids, const int k_)
{
	Centroids cntrds;
	ColorBuf buffer[K];
	sf::Color pixel;
	int w = img.getSize().x;
	int h = img.getSize().y;
	for (int i = 0; i < ids.size(); ++i)
	{

		int h_pixel = i / w;
		int w_pixel = i - h_pixel * w;
		pixel = img.getPixel(w_pixel, h_pixel);
		buffer[ids[i]] += pixel;
	}
	for (int i = 0; i < k_; i++)
	{
		buffer[i].normalize();
		cntrds.push_back(pixel);
		cntrds[i].r = buffer[i].r;
		cntrds[i].b = buffer[i].b;
		cntrds[i].g = buffer[i].g;
	}

	return cntrds;

}

void changeColors(sf::Image& img, const Centroids& cntrds)
{
	sf::Color pixel;
	int w = img.getSize().x;
	int h = img.getSize().y;
	for (int i = 0; i < w*h; ++i)
	{
		int h_pixel = i / w;
		int w_pixel = i - h_pixel * w;
		pixel = img.getPixel(w_pixel, h_pixel);
		float max = 100000;
		for (int j = 0; j < cntrds.size(); ++j)
		{
			float ds = distance(pixel, cntrds[j]);
			if (ds < max)
			{
				max = ds;
				img.setPixel(w_pixel, h_pixel, cntrds[j]);
			}
		}

	}
}

int main()
{
	sf::Image Im;
	Im.loadFromFile("page.png");

	sf::RenderWindow window(sf::VideoMode(Im.getSize().x, Im.getSize().y), "My window");

	Centroids centroids = initializeCentroids(Im, K);
	
	for (int it = 0; it < IterationCount; ++it)
	{
		ClosestCentroidIndies ids = findClosestCentroids(Im, centroids);
		centroids = computeMeans(Im, ids, K);
	}
	changeColors(Im, centroids);
	sf::Texture texture;
	texture.loadFromImage(Im);
	sf::Sprite photo(texture);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(photo);
		window.display();
	}

	return 0;
}
