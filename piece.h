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
		sf::Vector2f position;
	
		Piece(Type, sf::Vector2f);

		Piece& operator=(const Piece&);

		bool operator==(const Piece&) const;

		bool operator!=(const Piece&) const;
	};

	extern std::vector<Piece> white_pieces;
	extern std::vector<Piece> black_pieces;

	void LoadPieces(void) noexcept;

	std::string GetTextureFilename(Type, sf::Color) noexcept;
}