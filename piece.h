#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using sf::Sprite, sf::Color, sf::Vector2f;

namespace game
{
	enum Type : int
	{
		Pawn = 0,
		Rook = 1,
		Knight = 2,
		Bishop = 3,
		Queen = 4,
		King = 5
	};

	struct Piece
	{
		Type type;
		Sprite sprite;
	
		Piece(Type, Sprite);

		Piece(Type, Vector2f, Color);

		Piece& operator=(const Piece&);

		bool operator==(const Piece&) const;

		bool operator!=(const Piece&) const;
	};

	void LoadPieceSprite(Piece&) noexcept;
}