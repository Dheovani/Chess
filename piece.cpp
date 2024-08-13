#include "piece.h"

using namespace game;

using sf::Texture;

Piece::Piece(Type t, Sprite s) : type(t), sprite(s)
{}

Piece::Piece(Type t, Vector2f pos, Color color) : type(t)
{
	sprite.setColor(color);
	sprite.setPosition(pos);

	LoadPieceSprite(*this);
}

Piece& Piece::operator=(const Piece& other)
{
	type = other.type;
	sprite.setColor(other.sprite.getColor());
	sprite.setPosition(other.sprite.getPosition());
}

bool Piece::operator==(const Piece& other) const
{
	return type == other.type
		&& sprite.getColor() == other.sprite.getColor()
		&& sprite.getPosition() == other.sprite.getPosition();
}

bool Piece::operator!=(const Piece& other) const
{
	return type != other.type
		&& sprite.getColor() != other.sprite.getColor()
		&& sprite.getPosition() != other.sprite.getPosition();
}

void game::LoadPieceSprite(Piece& piece) noexcept
{
	Texture texture;

	// TODO: Load sprite icons texture files
	switch (piece.type) {
	case Pawn:
	case Rook:
	case Knight:
	case Bishop:
	case Queen:
	case King:
	default:
		throw "Not implemented yet";
	}

	piece.sprite.setTexture(texture);
}
