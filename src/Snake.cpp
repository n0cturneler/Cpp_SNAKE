#include "Snake.hpp"

#include "Options.hpp"
#include "Apple.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <print>
#include <vector>
#include <ranges>
#include <iterator>
#include <typeinfo>

using namespace Options;

Snake::Snake()
{
	// size is automatic in default
	m_object.setPosition(Game::defaultPosition);

	if (m_type == Type::head)
	{
		setColor(Colors::headColor, Colors::headOutlineColor, Colors::headOutlineThickness);
	}
	else if (m_type == Type::body)
	{
		m_length = 0;
		setColor(Colors::bodyColor, Colors::bodyOutlineColor, Colors::bodyOutlineThickness);
	}
}

Snake::Snake(Type type) : m_type{type}
{
	// size is automatic in default
	m_object.setPosition(Game::defaultPosition);

	if (m_type == Type::head)
	{	
		setColor(Colors::headColor, Colors::headOutlineColor, Colors::headOutlineThickness);
	}
	else if (m_type == Type::body)
	{
		m_length = 0;
		setColor(Colors::bodyColor, Colors::bodyOutlineColor, Colors::bodyOutlineThickness);
	}
}

Snake::Snake(Type type, sf::Vector2f& size, sf::Vector2f& position, sf::Color& mainColor, sf::Color& outlineColor, float outlineThickness, int length)
	: m_type{type}, m_length{length}
{
	m_object.setSize(size);
	m_object.setPosition(position);

	setColor(mainColor, outlineColor, outlineThickness);

	if (m_type == Type::body)
	{
		m_length = 0;
	}
}

Snake::~Snake()
{

}

void Snake::setColor(sf::Color mainColor, sf::Color outlineColor, float outlineThickness)
{
	m_object.setFillColor(mainColor);
	m_object.setOutlineColor(outlineColor);
	m_object.setOutlineThickness(outlineThickness);
}

std::vector<Snake> Snake::createSnake(int length, std::vector<sf::Vector2f>& snakePositions)
{
	std::vector<Snake> snakeArray{};
	
	for (int index{1}; index <= length; ++index)
	{	
		if (index == 1) // Create head
		{	
			Snake s{Type::head};
			snakeArray.push_back(s);
		}
		else
		{	
			Snake s{};
			
			if (index % 2 != 0 && length % 2 == 0)
			{	
				s.setColor(Colors::headColor, Colors::headOutlineColor, Colors::bodyOutlineThickness);
			}
			else if (index % 2 == 0 && length % 2 != 0)
			{
				s.setColor(Colors::headColor, Colors::headOutlineColor, Colors::bodyOutlineThickness);
			}
			snakeArray.push_back(s);
		}
	}

	for (sf::Vector2f& vector2 : snakePositions)
	{
		vector2.x = Options::Game::defaultPosition.x;
		vector2.y = Options::Game::defaultPosition.y;
	}

	return snakeArray;
}

void Snake::drawSnake(sf::RenderWindow& window, std::vector<Snake>& snakeArray)
{
	for (Snake& s : snakeArray | std::views::reverse)
	{
		window.draw(s.object());
	}
}

void Snake::updateSnake(std::vector<sf::Vector2f>& snakePositions, std::vector<Snake>& snakeArray, sf::Vector2f currentPosition, int currentLength)
{
	if (static_cast<int>(snakePositions.size()) < (currentLength)) // Head excluded
	{
		snakePositions.push_back(currentPosition);

		Snake s{};
		if (snakeArray.size() % 2 == 0)
		{
			s.setColor(Colors::headColor, Colors::headOutlineColor, Colors::bodyOutlineThickness);
		}
		snakeArray.insert(snakeArray.begin() + 1, s);
	}
	else
	{
		snakePositions.push_back(currentPosition);
		snakePositions.erase(snakePositions.begin());
	}

	/*for (Snake s : snakeArray)
	{
		std::cout << s.m_length;
	}

	for (const auto& vector2 : snakePositions)
	{
		std::print(" [{}, {}] ", vector2.x, vector2.y);
	}

	std::println();*/

}

sf::Keyboard::Key Snake::getInput(sf::Keyboard::Key currentInput, Snake::Direction direction)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (direction != Snake::Direction::down))
	{
		currentInput = sf::Keyboard::Key::W;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (direction != Snake::Direction::up))
	{
		currentInput = sf::Keyboard::Key::S;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (direction != Snake::Direction::right))
	{
		currentInput = sf::Keyboard::Key::A;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (direction != Snake::Direction::left))
	{
		currentInput = sf::Keyboard::Key::D;
	}
	return currentInput;
}

void Snake::moveSnake(std::vector<Snake>& snakeArray, std::vector<sf::Vector2f>& snakePositions, sf::Keyboard::Key currentInput)
{
	using enum sf::Keyboard::Key;

	for (std::size_t index = 0; Snake& s : snakeArray)
	{	
		if (s.m_type == Type::head)
		{	
			switch (currentInput)
			{
			case W:
				s.m_object.move({0.0f, -Game::speedY});
				s.m_direction = Snake::Direction::up;
				break;

			case S:
				s.m_object.move({0.0f, Game::speedY});
				s.m_direction = Snake::Direction::down;
				break;

			case A:
				s.m_object.move({-Game::speedX, 0.0f});
				s.m_direction = Snake::Direction::left;
				break;

			case D:
				s.m_object.move({Game::speedX, 0.0f});
				s.m_direction = Snake::Direction::right;
				break;

			default:
				s.m_object.move({0.0f, 0.0f});
				s.m_direction = Snake::Direction::none;
				break;
			}
		}
		else if (s.m_type == Type::body)
		{	
			if (index <= (snakePositions.size() - 1))
			{
				snakeArray.at(index).object().setPosition(snakePositions.at(index)); // The first index is the head
			}
			else
			{
				snakeArray.at(index).object().setPosition(snakePositions.back());
			}
			
		}

		++index;
	}

}

bool Snake::checkBounds(std::vector<Snake>& snakeArray)
{	
	Snake snakeHead{snakeArray[0]};

	if ((snakeHead.position().x > Options::Game::positionBounds.x) || (snakeHead.position().y > Options::Game::positionBounds.y)
		|| (snakeHead.position().x < 0) || (snakeHead.position().y < 0)
		)
	{
		return false;
	}

	for (Snake& s : snakeArray)
	{
		if (s.type() == Type::body && snakeHead.position() == s.position() && snakeHead.direction() != Direction::none)
		{
			return false;
		}
	}
	return true;
}
