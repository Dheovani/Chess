#include "piece.h"

using namespace game;

using sf::Texture;

std::vector<Piece> game::white_pieces = {};
std::vector<Piece> game::black_pieces = {};

Piece::Piece(Type t, sf::Vector2f p) : type(t), position(p)
{}

Piece& Piece::operator=(const Piece& other)
{
	type = other.type;
	position = other.position;

	return *this;
}

bool Piece::operator==(const Piece& other) const
{
	return type == other.type
		&& position == other.position;
}

bool Piece::operator!=(const Piece& other) const
{
	return type != other.type
		&& position != other.position;
}

void game::LoadPieces(void) noexcept
{
	for (int i = 0; i < 8; ++i) {
		black_pieces.push_back(Piece(Pawn, sf::Vector2f(i * 100.f, 100.f)));
		white_pieces.push_back(Piece(Pawn, sf::Vector2f(i * 100.f, 600.f)));

		Type type;
		switch (i) {
		case 0:
		case 7: type = Rook;
			break;
		case 1:
		case 6: type = Knight;
			break;
		case 2:
		case 5: type = Bishop;
			break;
		case 3: type = Queen;
			break;
		case 4:
		default: type = King;
		}

		black_pieces.push_back(Piece(type, sf::Vector2f(i * 100.f, 0.f)));
		white_pieces.push_back(Piece(type, sf::Vector2f(i * 100.f, 700.f)));
	}
}

std::string game::GetTextureFilename(Type type, sf::Color color = sf::Color::Black) noexcept
{
	const bool blackPiece = color == sf::Color::Black;

	switch (type) {
	case Pawn:
		return std::string(assets_dir_path) + (blackPiece ? "black_pawn.png" : "white_pawn.png");

	case Rook:
		return std::string(assets_dir_path) + (blackPiece ? "black_rook.png" : "white_rook.png");

	case Knight:
		return std::string(assets_dir_path) + (blackPiece ? "black_knight.png" : "white_knight.png");

	case Bishop:
		return std::string(assets_dir_path) + (blackPiece ? "black_bishop.png" : "white_bishop.png");

	case Queen:
		return std::string(assets_dir_path) + (blackPiece ? "black_queen.png" : "white_queen.png");

	case King:
	default:
		return std::string(assets_dir_path) + (blackPiece ? "black_king.png" : "white_king.png");
	}
}
