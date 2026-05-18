#include <SFML/Graphics.hpp>

#include "Options.h"

#include <cstdint>

using namespace Options;

namespace Background
{
	constexpr unsigned int squarePerRow{static_cast<unsigned int>(Video::resX / Game::size.x)};
	constexpr unsigned int squarePerColumn{static_cast<unsigned int>(Video::resY / Game::size.y)};

	void drawBackground(sf::RenderWindow& window, sf::RectangleShape& tile) // this is gonna be hardcoded 16 x 16 since res is 800 and snake size is 50 // nevermind i made it dynamic :)
	{
		float offset{};

		for (int index_column{}; index_column < squarePerColumn; ++index_column)
		{
			offset = 0.0f;
			if (index_column % 2 == 0) { offset = -Game::size.x; }

			for (int index_row{}; index_row <= squarePerRow; ++index_row)
			{
				tile.setPosition({0.0f, 0.0f});

				if (index_row % 2 == 0)
				{
					tile.setFillColor(Colors::BGMainColor);
					tile.setOutlineColor(Colors::BGMainColorBorder);
					tile.move({(Game::size.x * index_row) + offset, Game::size.y * index_column});
					window.draw(tile);
				}
				else
				{
					tile.setFillColor(Colors::BGAltColor);
					tile.setOutlineColor(Colors::BGAltColorBorder);
					tile.move({(Game::size.x * index_row) + offset, Game::size.y * index_column});
					window.draw(tile);
				}
			}
		}
	}
}
