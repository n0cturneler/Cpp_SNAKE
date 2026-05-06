#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{	
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8; // aa level 8

	sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake Game!", sf::Style::Default, sf::State::Windowed, settings);
	window.setVerticalSyncEnabled(true); // vsync on

	sf::RectangleShape snakeHead({50.0f, 50.0f});
	snakeHead.setFillColor(sf::Color::Green);
	snakeHead.setOrigin({25.0f, 25.0f});
	snakeHead.setPosition({400.0f, 300.0f});

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {window.close();}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			snakeHead.move({5.0f, 0.0f});
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			snakeHead.move({-5.0f, 0.0f});
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			snakeHead.move({0.0f, -5.0f});
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			snakeHead.move({0.0f, 5.0f});
		}

		window.clear(sf::Color::Black);
		
		snakeHead.rotate(sf::degrees(0.25));
		window.draw(snakeHead);
		
		window.display();
	}
}
