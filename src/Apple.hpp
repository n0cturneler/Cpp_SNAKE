#pragma once

#include "Options.hpp"
#include "Snake.hpp"

#include <vector>

#include <SFML/Graphics.hpp>

class Snake;

class Apple
{
public:
	Apple(sf::Vector2f position);
	Apple(sf::Vector2f position, int amount);
	Apple(sf::Vector2f position, sf::Color mainColor, sf::Color outlineColor, int amount);

	~Apple();

	static void setApples(std::vector<Apple>& appleArray, std::vector<Snake>& snakeArray);
	static void drawApples(sf::RenderWindow& window, std::vector<Apple>& appleArray);
	static int updateApples(std::vector<Apple>& appleArray, std::vector<Snake>& snakeArray, int currentLength);

	void setColor(sf::Color mainColor, sf::Color outlineColor, float outlineThickness);
	sf::Vector2f position() const { return m_object.getPosition(); }

	int amount() { return m_amount; }
	sf::RectangleShape& object() { return m_object; }

private:
	sf::RectangleShape m_object{Options::Game::snakeSize};
	int m_amount{Options::Game::appleAmount};
};
