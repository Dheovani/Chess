#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

namespace game
{
	constexpr unsigned int window_wh = 800;

	extern sf::RenderWindow window;

	extern sf::Vector2f selected_position;

	// Checks for events
	void WatchEvents(void) noexcept;

	// Draws the board's squares
	void DrawBoard(void) noexcept;

	// Main event loop
	void Run(void);
}