#include "Snake.h"
#include "Options.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace Options;

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
		m_length = 0;
		m_object.setFillColor(Colors::bodyColor);
		m_object.setOutlineColor(Colors::bodyOutlineColor);
		m_object.setOutlineThickness(Colors::bodyOutlineThickness);
	}
}

Snake::Snake(sf::Vector2f& size, sf::Vector2f& position, sf::Color& headColor, sf::Color& bodyColor, int length)
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
		m_length = 0;
		m_object.setFillColor(Colors::bodyColor);
		m_object.setOutlineColor(Colors::bodyOutlineColor);
		m_object.setOutlineThickness(Colors::bodyOutlineThickness);
	}
}

Snake::~Snake()
{
	
}

sf::Keyboard::Key Snake::getInput(sf::Keyboard::Key currentInput) const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (m_direction != Snake::Direction::down))
	{
		currentInput = sf::Keyboard::Key::W;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (m_direction != Snake::Direction::up))
	{
		currentInput = sf::Keyboard::Key::S;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (m_direction != Snake::Direction::right))
	{
		currentInput = sf::Keyboard::Key::A;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (m_direction != Snake::Direction::left))
	{
		currentInput = sf::Keyboard::Key::D;
	}
	return currentInput;
}

void Snake::moveSnake(sf::Keyboard::Key currentInput)
{	
	using enum sf::Keyboard::Key;

	switch (currentInput)
	{
	case W:
		m_object.move({0.0f, -Game::speed});
		m_direction = Snake::Direction::up;
		break;

	case S:
		m_object.move({0.0f, Game::speed});
		m_direction = Snake::Direction::down;
		break;

	case A:
		m_object.move({-Game::speed, 0.0f});
		m_direction = Snake::Direction::left;
		break;

	case D:
		m_object.move({Game::speed, 0.0f});
		m_direction = Snake::Direction::right;
		break;

	default:
		m_object.move({0.0f, 0.0f});
		m_direction = Snake::Direction::none;
		break;
	}
}
