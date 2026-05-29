#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "GUI.h"
#include "Options.hpp"
#include "Snake.hpp"
#include "Background.hpp"
#include "Apple.hpp"

#include <iostream>
#include <cstdint>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <format>
#include <filesystem>

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8; // aa level 8
	// sf::VideoMode mode = sf::VideoMode::getDesktopMode(); // get user resolution

	sf::RenderWindow window(sf::VideoMode({Options::Video::resX, Options::Video::resY}), "Snake Game!", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(Options::Video::frameRate);
	
	//IMGUI
	GUI gui{window};

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
		sf::Time elapsed{clock.restart()};
		float dt{elapsed.asSeconds()};

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
			ImGui::SFML::ProcessEvent(window, *event);
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
		}

		window.clear(sf::Color::Black);

		Background::drawBackground(window);

		//Draw Objects
		Apple::drawApples(window, appleArray);
		Snake::drawSnake(window, snakeArray);

		gui.renderGUI(elapsed, snakeArray, gameStart);
		window.display();
	}
}

//Goal: make cool shit
