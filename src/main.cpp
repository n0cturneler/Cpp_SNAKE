#include "Profiler.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <optional>

int main()
{
	std::cout << "Hello, World!";

	sf::RenderWindow window(sf::VideoMode({800, 800}), "TITLE");

	sf::CircleShape	shape(100.0);

	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();
		window.draw(shape);
		window.display();

	}

	return 0;
}
