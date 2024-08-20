#pragma once

#include <memory>
#include "piece.h"
#include <SFML/Graphics.hpp>

namespace game
{
	constexpr unsigned int window_wh = 800;

	extern sf::RenderWindow window;

	extern sf::Vector2f selected_position;

	extern bool player_turn;

	// Verifies if someone won (and draws the win/lose screen)
	bool GameOver(void) noexcept;

	// Moves a piece to a new location
	void Move(Piece, sf::Vector2f) noexcept;

	// Moves a black piece to a new location randomly
	void MoveBlackPiece(void) noexcept;

	// Checks for events
	void WatchEvents(void) noexcept;

	// Draws the board's squares
	void DrawBoard(void) noexcept;

	// Main event loop
	void Run(void);
}