#include "piece.h"

using namespace game;

using sf::Texture;

std::vector<Piece> game::white_pieces = {};
std::vector<Piece> game::black_pieces = {};

Piece::Piece(Type t, sf::Color c, sf::Vector2f p)
	: type(t), color(c), position(p)
{}

Piece& Piece::operator=(const Piece& other)
{
	type = other.type;
	color = other.color;
	position = other.position;

	return *this;
}

bool Piece::operator==(const Piece& other) const
{
	return type == other.type
		&& color == other.color
		&& position == other.position;
}

bool Piece::operator!=(const Piece& other) const
{
	return type != other.type
		&& color != other.color
		&& position != other.position;
}

void game::LoadPieces() noexcept
{
	for (int i = 0; i < 8; ++i) {
		black_pieces.push_back(Piece(Pawn, sf::Color::Black, sf::Vector2f(i * 100.f, 100.f)));
		white_pieces.push_back(Piece(Pawn, sf::Color::White, sf::Vector2f(i * 100.f, 600.f)));

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

		black_pieces.push_back(Piece(type, sf::Color::Black, sf::Vector2f(i * 100.f, 0.f)));
		white_pieces.push_back(Piece(type, sf::Color::White, sf::Vector2f(i * 100.f, 700.f)));
	}
}

std::string game::GetTextureFilename(Type type, sf::Color color = sf::Color::Black) noexcept
{
	const bool blackPiece = color == sf::Color::Black;

	// TODO: Substituir as imagens por outras melhores
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

Piece game::GetPieceByPosition(sf::Vector2f position) noexcept
{
	for (const Piece& piece : white_pieces) {
		if (piece.position == position)
			return piece;
	}

	for (const Piece& piece : black_pieces) {
		if (piece.position == position)
			return piece;
	}

	return Piece(Pawn, sf::Color::Transparent, { -1.f, -1.f });
}

bool game::IsPositionOccupied(sf::Vector2f position) noexcept
{
	auto piece = game::GetPieceByPosition(position);
	return piece.position == position
		&& piece.position.x != -1.f
		&& piece.position.y != -1.f;
}
