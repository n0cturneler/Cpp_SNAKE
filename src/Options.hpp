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

		inline constexpr sf::Vector2f default_position{(static_cast<float>(Video::resX) - snakeSize.x) / 2, (static_cast<float>(Video::resY) - snakeSize.y) / 2};

		inline constexpr std::size_t length{6};

		inline constexpr int rate{10};

		inline constexpr float speed{50.0f};
	}

	namespace Colors
	{
		//SNAKE
		inline constexpr sf::Color headColor{255, 255, 59};
		inline constexpr sf::Color bodyColor{96, 255, 82};
		inline constexpr sf::Color appleColor{sf::Color::Red};

		inline constexpr sf::Color headOutlineColor{175, 175, 0};
		inline constexpr sf::Color bodyOutlineColor{33, 148, 40};

		inline constexpr float headOutlineThickness{Game::snakeSize.x / 6};
		inline constexpr float bodyOutlineThickness{-Game::snakeSize.x / 8};

		//BACKGROUND
		inline constexpr sf::Color BGMainColor{100, 100, 100};
		inline constexpr sf::Color BGMainColorBorder{80, 80, 80};

		inline constexpr sf::Color BGAltColor{70, 70, 70};
		inline constexpr sf::Color BGAltColorBorder{50, 50, 50};

		inline constexpr float BGoutlineThickness{-Game::snakeSize.x / 10};

		//APPLE
	}
}
