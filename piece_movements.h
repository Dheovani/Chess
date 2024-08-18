#pragma once

#include "piece.h"

namespace game
{
	std::vector<sf::Vector2f> CalculatePawnMoves(const Piece&) noexcept;

	std::vector<sf::Vector2f> CalculateRookMoves(const Piece&) noexcept;

	std::vector<sf::Vector2f> CalculateKnightMoves(const Piece&) noexcept;

	std::vector<sf::Vector2f> CalculateBishopMoves(const Piece&) noexcept;

	std::vector<sf::Vector2f> CalculateQueenMoves(const Piece&) noexcept;

	std::vector<sf::Vector2f> CalculateKingMoves(const Piece&) noexcept;

	// Calculate a piece's possible next moves
	std::vector<sf::Vector2f> CalculatePieceMoves(const Piece&) noexcept;
}