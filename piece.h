#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using sf::Vector2f;

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
		Vector2f position;
	
		Piece(Type, Vector2f);

		Piece& operator=(const Piece&);

		bool operator==(const Piece&) const;

		bool operator!=(const Piece&) const;
	};

	extern std::vector<Piece> white_pieces;
	extern std::vector<Piece> black_pieces;

	void LoadPieces(void) noexcept;
}