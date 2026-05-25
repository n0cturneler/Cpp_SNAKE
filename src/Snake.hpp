#pragma once
#include "Options.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

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
	Type m_type{Type::body};

	int m_length{Options::Game::length};

public:
	Snake();
	Snake(Type type);
	Snake(Type type, sf::Vector2f& size, sf::Vector2f& position, sf::Color& mainColor, sf::Color& outlineColor, float headOutlineThickness, int length);
	~Snake();

	void changeColor(sf::Color mainColor, sf::Color outlineColor);

	Direction direction() const { return m_direction; }
	sf::Vector2f position() const { return m_object.getPosition(); }
	
	sf::RectangleShape& object() { return m_object; }

	static std::vector<Snake> createSnake(int length, std::vector<sf::Vector2f>& bodyPosVec);
	static void drawSnake(sf::RenderWindow& window, std::vector<Snake>& snakeArray);
	static void updateSnake(std::vector<sf::Vector2f>& bodyPosVec, std::vector<Snake>& snakeArray, sf::Vector2f currentPosition, int currentLength);

	static sf::Keyboard::Key getInput(sf::Keyboard::Key currentInput, Snake::Direction direction);
	static void moveSnake(std::vector<Snake>& snakeArray, std::vector<sf::Vector2f>& bodyPosVec, sf::Keyboard::Key currentInput);
};
