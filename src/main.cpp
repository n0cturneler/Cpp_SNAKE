#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

#include <iostream>
#include <cstdint>
#include <typeinfo>

namespace Options
{
	constexpr unsigned int frameRate{60};
	constexpr int snakeRate{2};

	constexpr unsigned int resX{800};
	constexpr unsigned int resY{800};
}

namespace Background
{
	void drawBackground(unsigned int resX, unsigned int resY, sf::Vector2f& snakeSize, sf::RenderWindow& window) // this is gonna be hardcoded 16 x 16 since res is 800 and snake size is 50
	{	
		int squarePerRow{(static_cast<int>(resX) / static_cast<int>(snakeSize.x))};
		int squarePerColumn{(static_cast<int>(resY) / static_cast<int>(snakeSize.y))};
		int squareCount{squarePerRow * squarePerColumn};

		float offset{};
		
		for (int index_column{}; index_column < squarePerColumn; ++index_column)
		{	
			offset = 0;
			if (index_column % 2 == 0) { offset = -snakeSize.x; }

			for (int index_row{}; index_row <= squarePerRow; ++index_row)
			{	
				if (index_row % 2 == 0)
				{
					sf::RectangleShape tile{snakeSize};
					tile.setFillColor({50, 50, 50});
					tile.setPosition({0.0f, 0.0f});
					tile.move({(snakeSize.x * index_row) + offset, snakeSize.y * index_column});
					window.draw(tile);
				}
				else
				{
					sf::RectangleShape tile{snakeSize};
					tile.setFillColor({80, 80, 80});
					tile.setPosition({0.0f, 0.0f});
					tile.move({(snakeSize.x * index_row) + offset, snakeSize.y * index_column});
					window.draw(tile);
				}
			}
		}
	}
}

namespace Snake
{
	sf::Vector2f size{50.0f, 50.0f};

	sf::Color headColor{sf::Color::Yellow};
	sf::Color bodyColor{sf::Color::Green};
	sf::Color appleColor{sf::Color::Red};

	sf::Color snakeHeadOutline{sf::Color {175, 175, 0}};
	
	float outlineThickness{size.x/6};
	float speed{50.0f};

	enum class Direction
	{
		none,
		up,
		down,
		left,
		right,
	};

	class SnakeHead
	{
	public:
		SnakeHead()
		{
			// size is automatic in default
			m_object.setPosition(default_position);
			m_object.setOutlineColor(snakeHeadOutline);
			m_object.setOutlineThickness(outlineThickness);
			m_object.setFillColor(m_color);
		}

		SnakeHead(sf::Vector2f size, sf::Vector2f position, sf::Color color, int length)
			: default_position{position}, m_color{color}, m_length{length}
		{
			m_object.setSize(size);
			m_object.setPosition(default_position);
			m_object.setOutlineColor(snakeHeadOutline);
			m_object.setOutlineThickness(outlineThickness);
			m_object.setFillColor(m_color);
		}

		void setDirection(Direction direction) { m_direction = direction; }

		void moveSnake()
		{
			using enum Direction;
			switch (m_direction)
			{
			case none:
				break;

			case up:
				m_object.move({0.0f, -speed});
				break;

			case down:
				m_object.move({0.0f, speed});
				break;

			case left:
				m_object.move({-speed, 0.0f});
				break;

			case right:
				m_object.move({speed, 0.0f});
				break;

			default:
				break;
			}
		}

		const sf::RectangleShape& object() const { return m_object; }

	private:
		sf::RectangleShape m_object{size};
		sf::Color m_color{headColor};

		sf::Vector2f default_position{0.0f, 0.0f};
		Direction m_direction{Direction::none};
		int m_length{1};

	};

	template <typename T>
	void moveObject(T& object, sf::Vector2i position)
	{
		object.move(position);
	}

}

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8; // aa level 8

	sf::VideoMode mode = sf::VideoMode::getDesktopMode(); // get user resolution

	sf::RenderWindow window(sf::VideoMode({Options::resX, Options::resY}), "Snake Game!", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(Options::frameRate);

	Snake::SnakeHead snakeHead{};

	sf::Clock clock;
	std::uint64_t currentCycle{};
	float cycleProgress{};

	float tickRate{1.0f / Options::frameRate};

	while (window.isOpen())
	{
		//Compute frame times
		float dt{clock.restart().asSeconds()};

		cycleProgress += dt;
		if (cycleProgress >= tickRate)
		{
			cycleProgress -= tickRate;
			++currentCycle;
		}

		//Events
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		window.clear(sf::Color::Black);

		// Draw checkered pattern
		Background::drawBackground(Options::resX, Options::resY, Snake::size, window);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			snakeHead.setDirection(Snake::Direction::up);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			snakeHead.setDirection(Snake::Direction::down);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			snakeHead.setDirection(Snake::Direction::left);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			snakeHead.setDirection(Snake::Direction::right);
		}

		if (currentCycle % (Options::frameRate/Options::snakeRate) == 0)
		{
			snakeHead.moveSnake();
		}

		window.draw(snakeHead.object());

		window.display();
	}
}

//Goal: make cool shit
