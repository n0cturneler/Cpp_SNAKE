#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

#include "Options.hpp"
#include "Snake.hpp"
#include "Background.hpp"

#include <iostream>
#include <cstdint>
#include <optional>
#include <print>

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8; // aa level 8

	// sf::VideoMode mode = sf::VideoMode::getDesktopMode(); // get user resolution

	sf::RenderWindow window(sf::VideoMode({Options::Video::resX, Options::Video::resY}), "Snake Game!", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(Options::Video::frameRate);

	//Snake creation
	std::vector<sf::Vector2f> snakeBodyPositions(Options::Game::length - 1); // Head excluded

	std::vector<Snake> snakeArray(Snake::createSnake(Options::Game::length, snakeBodyPositions));
	std::size_t headIndex {Options::Game::length - 1};

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
		currentInput = Snake::getInput(currentInput, snakeArray[headIndex].direction());

		if (currentCycle % std::uint64_t((Options::Video::frameRate / Options::Game::rate)) == 0)
		{	
			Snake::updateSnake(snakeBodyPositions, snakeArray[headIndex].position());
			Snake::moveSnake(snakeArray, snakeBodyPositions, currentInput);

			 // std::println("Head pos: [{}, {}] ^ ", snakeArray[headIndex].position().x, snakeArray[headIndex].position().y);
		}

		window.clear(sf::Color::Black);

		// Draw checkered pattern
		Background::drawBackground(window);
		Snake::drawSnake(window, snakeArray);

		window.display();
	}
}

//Goal: make cool shit
