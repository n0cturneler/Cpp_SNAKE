#pragma once
#include "Options.h"

#include <SFML/Graphics.hpp>

using namespace Options;

class Snake
{
public:
	enum class Direction
	{
		none,
		up,
		down,
		left,
		right,
	};

	enum class Type
	{
		head,
		body,
	};

private:
	sf::RectangleShape m_object{Game::size};

	Direction m_direction{Direction::none};
	Type m_type{Type::head};

	int m_length{Game::length};

public:
	Snake();
	Snake(sf::Vector2f size, sf::Vector2f position, sf::Color headColor, sf::Color bodyColor, int length);

	void moveSnake();
	void setDirection(Direction direction) { m_direction = direction; }

	const Direction& direction() const { return m_direction; }
	const sf::Vector2f& position() const { return m_object.getPosition(); }

	const sf::RectangleShape& object() const { return m_object; }

};
