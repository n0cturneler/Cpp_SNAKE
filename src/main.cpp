#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>

#include "Options.hpp"
#include "Snake.hpp"
#include "Background.hpp"
#include "Apple.hpp"

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
	std::vector<sf::Vector2f> snakePositions(Options::Game::length);
	std::vector<Snake> snakeArray{Snake::createSnake(Options::Game::length, snakePositions)};

	std::size_t headIndex{0};
	int currentLength{Options::Game::length};

	//Apple creation
	std::vector<Apple> appleArray{};

	//Game clock and cycle
	sf::Clock clock;
	std::uint64_t currentCycle{};
	float cycleProgress{};
	float tickRate{1.0f / Options::Video::frameRate};

	[[maybe_unused]] bool gameStart{true};

	sf::Keyboard::Key currentInput{sf::Keyboard::Key::Unknown};

	while (window.isOpen())
	{
		//Compute frame times
		float dt{clock.restart().asSeconds()};

		// std::println("FPS: {}", 1/dt);

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

		if (gameStart)
		{
			//Input
			currentInput = Snake::getInput(currentInput, snakeArray[headIndex].direction());

			if (currentCycle % std::uint64_t((Options::Video::frameRate / Options::Game::cycleRate)) == 0)
			{
				Apple::setApples(appleArray, snakeArray);

				currentLength = Apple::updateApples(appleArray, snakeArray, currentLength);
				Snake::updateSnake(snakePositions, snakeArray, snakeArray[headIndex].position(), currentLength);
				Snake::moveSnake(snakeArray, snakePositions, currentInput);

				gameStart = Snake::checkBounds(snakeArray);

				//std::println("Head pos: [{}, {}]", snakeArray[headIndex].position().x, snakeArray[headIndex].position().y);			
			}

			if (gameStart) // exit so we keep the pre collision image
			{
				window.clear(sf::Color::Black);

				//Draw checkered pattern
				Background::drawBackground(window);

				//Draw Objects
				Apple::drawApples(window, appleArray);
				Snake::drawSnake(window, snakeArray);

				window.display();
			}

		}
	}
	std::println("Final Length: {}", snakeArray.size());
}

//Goal: make cool shit
