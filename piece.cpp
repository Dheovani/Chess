#include "piece.h"

using namespace game;

using sf::Texture;

std::vector<Piece> game::white_pieces = {};
std::vector<Piece> game::black_pieces = {};

Piece::Piece(Type t, Vector2f p) : type(t), position(p)
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

static Type GetTypeByPos(int i) noexcept
{
	switch (i) {
	case 1:
	case 8:
		return Rook;
	case 2:
	case 7:
		return Knight;
	case 3:
	case 6:
		return Bishop;
	case 4:
		return Queen;
	case 5:
	default:
		return King;
	}
}

void game::LoadPieces(void) noexcept
{
	for (int i = 0; i < 8; ++i) {
		black_pieces.push_back(Piece(Pawn, Vector2f(i * 100.f, 100.f)));
		white_pieces.push_back(Piece(Pawn, Vector2f(i * 100.f, 600.f)));

		black_pieces.push_back(Piece(GetTypeByPos(i), Vector2f(i * 100.f, 0.f)));
		white_pieces.push_back(Piece(GetTypeByPos(i), Vector2f(i * 100.f, 700.f)));
	}
}
