#pragma once

#include <SFML/Graphics.hpp>

using sf::Vector2f;

namespace game
{
	enum Types : int
	{
		Pawn = 0,
		Tower = 1,
		Horse = 2,
		Bishop = 3,
		Queen = 4,
		King = 5
	};

	struct Piece
	{
		Vector2f pos;
	};
}