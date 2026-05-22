#pragma once

#include <SFML/Graphics.hpp>

namespace Options
{	
	namespace Video
	{
		inline constexpr unsigned int frameRate{60};

		inline constexpr unsigned int resX{950};
		inline constexpr unsigned int resY{950};
	}
	
	namespace Game
	{
		inline constexpr sf::Vector2f snakeSize{50.0f, 50.0f};

		inline constexpr sf::Vector2f default_position{0.0f, 0.0f};

		inline constexpr int length{5};

		inline int rate{5};

		inline float speed{50.0f};
	}

	namespace Colors
	{
		//SNAKE
		inline constexpr sf::Color headColor{sf::Color::Yellow};
		inline constexpr sf::Color bodyColor{sf::Color::Green};
		inline constexpr sf::Color appleColor{sf::Color::Red};

		inline constexpr sf::Color headOutlineColor{sf::Color{175, 175, 0}};
		inline constexpr sf::Color bodyOutlineColor{sf::Color{46, 112, 46}};

		inline constexpr float headOutlineThickness{Game::snakeSize.x / 6};
		inline constexpr float bodyOutlineThickness{Game::snakeSize.x / 8};

		//BACKGROUND
		inline constexpr sf::Color BGMainColor{100, 100, 100};
		inline constexpr sf::Color BGMainColorBorder{80, 80, 80};

		inline constexpr sf::Color BGAltColor{70, 70, 70};
		inline constexpr sf::Color BGAltColorBorder{50, 50, 50};

		inline float BGoutlineThickness{-Game::snakeSize.x / 10};

		//APPLE
	}
}
