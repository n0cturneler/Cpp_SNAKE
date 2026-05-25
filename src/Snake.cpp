#include "Snake.hpp"
#include "Options.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <print>
#include <vector>

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

Snake::Snake(Type type) : m_type{type}
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

Snake::Snake(Type type, sf::Vector2f& size, sf::Vector2f& position, sf::Color& mainColor, sf::Color& outlineColor, float headOutlineThickness, int length)
	: m_type{type}, m_length{length}
{
	m_object.setSize(size);
	m_object.setPosition(position);

	m_object.setFillColor(mainColor);
	m_object.setOutlineColor(outlineColor);
	m_object.setOutlineThickness(headOutlineThickness);

	if (m_type == Type::body)
	{
		m_length = 0;
	}
}

Snake::~Snake()
{

}

void Snake::changeColor(sf::Color mainColor, sf::Color outlineColor)
{
	m_object.setFillColor(mainColor);
	m_object.setOutlineColor(outlineColor);
}

std::vector<Snake> Snake::createSnake(int length, std::vector<sf::Vector2f>& bodyPosVec)
{
	std::vector<Snake> snakeArray{};

	
	for (int index{1}; index <= length; ++index)
	{	
		if (index == length) // Create head
		{	
			Snake s{Type::head};
			snakeArray.push_back(s);
		}
		else
		{	
			Snake s{};
			
			if (index % 2 != 0 && length % 2 != 0)
			{	
				s.changeColor(Options::Colors::headColor, Options::Colors::headOutlineColor);
			}
			else if (index % 2 == 0 && length % 2 == 0)
			{
				s.changeColor(Options::Colors::headColor, Options::Colors::headOutlineColor);
			}
			snakeArray.push_back(s);
		}
	}

	for (auto& vector2 : bodyPosVec)
	{
		vector2.x = Options::Game::default_position.x;
		vector2.y = Options::Game::default_position.y;
	}

	return snakeArray;
}

void Snake::drawSnake(sf::RenderWindow& window, std::vector<Snake>& snakeArray)
{
	for (Snake& s : snakeArray)
	{
		window.draw(s.object());
	}
}

void Snake::updateSnake(std::vector<sf::Vector2f>& bodyPosVec, std::vector<Snake>& snakeArray, sf::Vector2f currentPosition, int currentLength)
{
	if (static_cast<int>(bodyPosVec.size()) < (currentLength - 1)) // Head excluded
	{
		bodyPosVec.push_back(currentPosition);

		Snake s{};
		snakeArray.insert(snakeArray.begin(), s);
	}
	else
	{
		bodyPosVec.push_back(currentPosition);
		bodyPosVec.erase(bodyPosVec.begin());
	}

	/*for (Snake s : snakeArray)
	{
		std::cout << s.m_length;
	}*/

	/*for (const auto& vector2 : bodyPosVec)
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

void Snake::moveSnake(std::vector<Snake>& snakeArray, std::vector<sf::Vector2f>& bodyPosVec, sf::Keyboard::Key currentInput)
{
	using enum sf::Keyboard::Key;

	for (std::size_t index = 0; Snake& s : snakeArray)
	{	
		if (s.m_type == Type::head)
		{	
			switch (currentInput)
			{
			case W:
				s.m_object.move({0.0f, -Game::speed});
				s.m_direction = Snake::Direction::up;
				break;

			case S:
				s.m_object.move({0.0f, Game::speed});
				s.m_direction = Snake::Direction::down;
				break;

			case A:
				s.m_object.move({-Game::speed, 0.0f});
				s.m_direction = Snake::Direction::left;
				break;

			case D:
				s.m_object.move({Game::speed, 0.0f});
				s.m_direction = Snake::Direction::right;
				break;

			default:
				s.m_object.move({0.0f, 0.0f});
				s.m_direction = Snake::Direction::none;
				break;
			}
		}
		else
		{	
			if (index <= (bodyPosVec.size() - 1))
			{
				snakeArray.at(index).object().setPosition(bodyPosVec.at(index));
			}
			else
			{
				snakeArray.at(index).object().setPosition(bodyPosVec.back());
			}
			
		}

		++index;
	}

}
