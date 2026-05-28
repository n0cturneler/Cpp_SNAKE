#pragma once

#include <SFML/Graphics.hpp>

namespace Options
{	
	namespace Video
	{
		inline constexpr int frameRate{120};

		inline constexpr int resX{950};
		inline constexpr int resY{950};
	}
	
	namespace Game
	{
		inline constexpr sf::Vector2f snakeSize{50.0f, 50.0f};
		inline constexpr float speedX{snakeSize.x};
		inline constexpr float speedY{snakeSize.y};
		inline constexpr sf::Vector2f positionBounds{(static_cast<float>(Video::resX) - snakeSize.x), (static_cast<float>(Video::resY) - snakeSize.y)};
		inline constexpr sf::Vector2f defaultPosition{positionBounds.x / 2, positionBounds.y / 2};

		inline constexpr std::size_t length{5};

		inline constexpr int cycleRate{10};

		inline constexpr int appleAmount{1};
		inline constexpr int maxApples{2};

		inline constexpr bool godMode{false};
	}

	namespace Colors
	{
		// SNAKE
			// HEAD
		inline constexpr sf::Color headColor{247, 255, 8};
		inline constexpr sf::Color headOutlineColor{175, 175, 0};
		inline constexpr float headOutlineThickness{Game::snakeSize.x / 6};

			// BODY
		inline constexpr sf::Color bodyColor{96, 255, 82};
		inline constexpr sf::Color bodyOutlineColor{33, 148, 40};
		inline constexpr float bodyOutlineThickness{-Game::snakeSize.x / 8};

		//APPLE
		inline constexpr sf::Color appleColor{255, 65, 51};
		inline constexpr sf::Color appleOutlineColor{110, 29, 23};
		inline constexpr float appleOutlineThickness{-Game::snakeSize.x / 6};

		//BACKGROUND
		inline constexpr sf::Color BGMainColor{100, 100, 100};
		inline constexpr sf::Color BGMainColorBorder{80, 80, 80};

		inline constexpr sf::Color BGAltColor{70, 70, 70};
		inline constexpr sf::Color BGAltColorBorder{50, 50, 50};

		inline constexpr float BGoutlineThickness{-Game::snakeSize.x / 10};

	}
}
