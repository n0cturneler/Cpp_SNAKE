#pragma once

#include "Snake.hpp"
#include "Apple.hpp"

#include <SFML/Window.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <vector>
#include <format>
#include <string>

class GUI
{
public:
	GUI(sf::RenderWindow& window)
		: m_window{window}
	{
		[[maybe_unused]] bool imgui_ok = ImGui::SFML::Init(window);
		assert(imgui_ok);

		ImGuiIO& io = ImGui::GetIO();

		ImFont* font = io.Fonts->AddFontFromFileTTF(
			"../../../../assets/fonts/COURIER_PRIME_CODE.TTF",
			18.0f
		);
		assert(font);
		io.FontDefault = font;

		bool font_ok = ImGui::SFML::UpdateFontTexture();

		if (!font_ok)
		{
			std::cerr << "Failed to update font texture\n";
		}

	}

	void renderGUI(sf::Time elapsed, std::vector<Snake> snakeArray, bool gameState) const
	{
		ImGui::SFML::Update(m_window, elapsed);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::Begin("Snake Data");

		std::string snakeLength = std::format("Length: {}", snakeArray.size());
		ImGui::Text("%s", snakeLength.c_str());

		std::string snakeDirection = std::format("Direction: {}", snakeArray[0].directionString());
		ImGui::Text("%s", snakeDirection.c_str());

		std::string snakeStatus = std::format("Alive: {}", gameState);
		ImGui::Text("%s", snakeStatus.c_str());

		std::string snakePosition = std::format("Position: [x : {}, y : {}]", snakeArray[0].position().x, snakeArray[0].position().y);
		ImGui::Text("%s", snakePosition.c_str());

		ImGui::End();

		ImGui::SFML::Render(m_window);
	}

	~GUI()
	{
		ImGui::SFML::Shutdown();
	}
private:
	sf::RenderWindow& m_window;


};

