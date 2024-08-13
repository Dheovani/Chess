#pragma once

#include "piece.h"
#include <memory>
#include <SFML/Graphics.hpp>

using sf::RenderWindow;

namespace game
{
	constexpr unsigned int window_wh = 800;

	typedef std::shared_ptr<RenderWindow> SWindow;

	// Displays the pieces
	void DisplayPieces(void) noexcept;

	// Draws the board's squares
	void DrawBoard(void) noexcept;

	// Generates the simulation's window
	SWindow GetWindow(void) noexcept;

	// Main event loop
	void Run(const SWindow&);
}