#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "piece.h"

using sf::RenderWindow;

namespace game
{
	constexpr unsigned int window_wh = 800;

	extern RenderWindow window;

	extern sf::Vector2f selected_position;

	// Draws the board's squares
	void DrawBoard(void) noexcept;

	// Main event loop
	void Run(void);
}