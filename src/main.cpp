#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

#include "Options.h"
#include "Snake.h"
#include "Background.h"

#include <iostream>
#include <cstdint>

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8; // aa level 8

	sf::VideoMode mode = sf::VideoMode::getDesktopMode(); // get user resolution

	sf::RenderWindow window(sf::VideoMode({Options::Video::resX, Options::Video::resY}), "Snake Game!", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(Options::Video::frameRate);

	//Redo this when main menu
	Snake snakeHead{};
	sf::RectangleShape tile{Options::Game::size};
	tile.setOutlineThickness(Options::Colors::BGoutlineThickness);

	sf::Clock clock;
	std::uint64_t currentCycle{};
	float cycleProgress{};

	float tickRate{1.0f / Options::Video::frameRate};

	while (window.isOpen())
	{
		//Compute frame times
		float dt{clock.restart().asSeconds()};

		cycleProgress += dt;
		if (cycleProgress >= tickRate)
		{
			cycleProgress -= tickRate;
			++currentCycle;
		}

		//Events
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		window.clear(sf::Color::Black);

		// Draw checkered pattern
		Background::drawBackground(window, tile);

		// Fix this input mess !!!
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (snakeHead.direction() != Snake::Direction::down))
		{
			snakeHead.setDirection(Snake::Direction::up);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (snakeHead.direction() != Snake::Direction::up))
		{
			snakeHead.setDirection(Snake::Direction::down);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (snakeHead.direction() != Snake::Direction::right))
		{
			snakeHead.setDirection(Snake::Direction::left);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (snakeHead.direction() != Snake::Direction::left))
		{
			snakeHead.setDirection(Snake::Direction::right);
		}

		if (currentCycle % (Options::Video::frameRate / Options::Game::rate) == 0)
		{
			snakeHead.moveSnake();
		}

		window.draw(snakeHead.object());

		window.display();
	}
}

//Goal: make cool shit
