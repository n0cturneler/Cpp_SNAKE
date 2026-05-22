#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

#include "Options.h"
#include "Snake.h"
#include "Background.h"

#include <iostream>
#include <cstdint>
#include <optional>

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8; // aa level 8

	sf::VideoMode mode = sf::VideoMode::getDesktopMode(); // get user resolution

	sf::RenderWindow window(sf::VideoMode({Options::Video::resX, Options::Video::resY}), "Snake Game!", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(Options::Video::frameRate);

	//Redo this when main menu
	Snake snakeHead{};
	sf::RectangleShape tile{Options::Game::snakeSize};
	tile.setOutlineThickness(Options::Colors::BGoutlineThickness);

	//Game clock and cycle
	sf::Clock clock;
	std::uint64_t currentCycle{};
	float cycleProgress{};

	float tickRate{1.0f / Options::Video::frameRate};

	sf::Keyboard::Key currentInput{sf::Keyboard::Key::Unknown};

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

		//Input
		currentInput = snakeHead.getInput(currentInput);

		if (currentCycle % (Options::Video::frameRate / Options::Game::rate) == 0)
		{
			snakeHead.moveSnake(currentInput);
			// std::cout << snakeHead.position().x << ", " << snakeHead.position().y << '\n';
		}

		window.clear(sf::Color::Black);

		// Draw checkered pattern
		Background::drawBackground(window, tile);
		window.draw(snakeHead.object());

		window.display();
	}
}

//Goal: make cool shit
