#pragma once
#include "Options.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
	sf::RectangleShape m_object{Options::Game::snakeSize};

	Direction m_direction{Direction::none};
	Type m_type{Type::head};

	int m_length{Options::Game::length};

public:
	Snake();
	Snake(sf::Vector2f& size, sf::Vector2f& position, sf::Color& headColor, sf::Color& bodyColor, int length);

	~Snake();

	void moveSnake(sf::Keyboard::Key currentInput);
	sf::Keyboard::Key getInput(sf::Keyboard::Key currentInput) const;

	Direction direction() const { return m_direction; }
	sf::Vector2f position() const { return m_object.getPosition(); }

	const sf::RectangleShape& object() const { return m_object; }

};
