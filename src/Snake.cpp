#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Options.h"

Snake::Snake()
{
	// size is automatic in default
	m_object.setPosition(Game::default_position);
	if (m_type == Type::head)
	{
		m_object.setFillColor(Colors::headColor);
		m_object.setOutlineColor(Colors::headOutlineColor);
		m_object.setOutlineThickness(Colors::headOutlineThickness);
		return;
	}
	else if (m_type == Type::body)
	{
		m_object.setFillColor(Colors::bodyColor);
		m_object.setOutlineColor(Colors::bodyOutlineColor);
		m_object.setOutlineThickness(Colors::bodyOutlineThickness);
	}
}

Snake::Snake(sf::Vector2f size, sf::Vector2f position, sf::Color headColor, sf::Color bodyColor, int length)
	: m_length{length}
{
	m_object.setSize(size);
	m_object.setPosition(position);

	if (m_type == Type::head)
	{
		m_object.setFillColor(Colors::headColor);
		m_object.setOutlineColor(Colors::headOutlineColor);
		m_object.setOutlineThickness(Colors::headOutlineThickness);
		return;
	}
	else if (m_type == Type::body)
	{
		m_object.setFillColor(Colors::bodyColor);
		m_object.setOutlineColor(Colors::bodyOutlineColor);
		m_object.setOutlineThickness(Colors::bodyOutlineThickness);
	}
}

void Snake::moveSnake()
{
	using enum Direction;
	switch (m_direction)
	{
	case none:
		break;

	case up:
		m_object.move({0.0f, -Game::speed});
		break;

	case down:
		m_object.move({0.0f, Game::speed});
		break;

	case left:
		m_object.move({-Game::speed, 0.0f});
		break;

	case right:
		m_object.move({Game::speed, 0.0f});
		break;

	default:
		break;
	}
}
