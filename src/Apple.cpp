#include "Apple.hpp"

#include "Random.hpp"
#include "Options.hpp"
#include "Snake.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>

#include <print>


using namespace Options;

Apple::Apple(sf::Vector2f position)
{	
	m_object.setPosition(position);
	setColor(Colors::appleColor, Colors::appleOutlineColor, Colors::appleOutlineThickness);
}

Apple::Apple(sf::Vector2f position, int amount) 
	: m_amount{amount}
{
	m_object.setPosition(position);
	setColor(Colors::appleColor, Colors::appleOutlineColor, Colors::appleOutlineThickness);
}

Apple::Apple(sf::Vector2f position, sf::Color mainColor, sf::Color outlineColor, int amount)
	: m_amount{amount}
{
	m_object.setPosition(position);
	setColor(mainColor, outlineColor, Colors::appleOutlineThickness);
}

Apple::~Apple()
{
	
}

void Apple::setColor(sf::Color mainColor, sf::Color outlineColor, float outlineThickness)
{
	m_object.setFillColor(mainColor);
	m_object.setOutlineColor(outlineColor);
	m_object.setOutlineThickness(outlineThickness);
}
	
void Apple::setApples(std::vector<Apple>& appleArray, std::vector<Snake>& snakeArray)
{
	for (int currentSize {static_cast<int>(appleArray.size())}; currentSize < Game::maxApples; ++currentSize)
	{	
		int possiblePosX{static_cast<int>(Game::positionBounds.x / Game::snakeSize.x)};
		int possiblePosY{static_cast<int>(Game::positionBounds.x / Game::snakeSize.x)};

		while (true)
		{	
			float x{};
			float y{};
			x = static_cast<float>(Random::get(0, possiblePosX) * static_cast<int>(Game::snakeSize.x));
			y = static_cast<float>(Random::get(0, possiblePosY) * static_cast<int>(Game::snakeSize.y));
			sf::Vector2f applePos{x, y};
			
			bool invalidPosition{false};
			for (const Snake& s : snakeArray)
			{
				if (s.position() == applePos)
				{	
					invalidPosition = true;
				}
			}

			for (const Apple& apple : appleArray)
			{
				if (apple.position() == applePos)
				{
					invalidPosition = true;
				}
			}

			if (invalidPosition) { continue; }

			//std::println("Apple pos: [{}, {}]", applePos.x, applePos.y);

			Apple apple{applePos};
			appleArray.push_back(apple);
			break;
		}
	}
}

void Apple::drawApples(sf::RenderWindow& window, std::vector<Apple>& appleArray)
{
	for (Apple& a : appleArray)
	{
		window.draw(a.object());
	}
}

int Apple::updateApples(std::vector<Apple>& appleArray, std::vector<Snake>& snakeArray, int currentLength)
{	
	int amount{};
	for (auto it = appleArray.begin(); it != appleArray.end();)
	{
		if (it->position() == snakeArray[0].position())
		{	
			amount = it->amount();
			it = appleArray.erase(it);
		}
		else
		{	
			++it;
		}
	}
	return currentLength += amount;
}
