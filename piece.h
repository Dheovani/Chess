#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace game
{
	constexpr const char* assets_dir_path = "..\\..\\..\\assets\\";

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
		sf::Color color;
		sf::Vector2f position;
	
		Piece(Type, sf::Color, sf::Vector2f);

		Piece& operator=(const Piece&);

		bool operator==(const Piece&) const;

		bool operator!=(const Piece&) const;
	};

	extern std::vector<Piece> white_pieces;

	extern std::vector<Piece> black_pieces;

	// Generates the pieces in the black and white piece vectors
	void LoadPieces(void) noexcept;

	// Returns the path to the texture filhe of the piece
	std::string GetTextureFilename(const Piece&) noexcept;

	// Returns the piece at the given position
	Piece GetPieceByPosition(sf::Vector2f) noexcept;

	// Verifies if a position is occupied
	bool IsPositionOccupied(sf::Vector2f) noexcept;
}