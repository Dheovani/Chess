#include "piece_movements.h"
#include "utils.h"
#include <functional>

using namespace game;

// Verifies if the occupied position is the position of an ally
static bool IsPositionFilledByAlly(const Piece& piece, const sf::Vector2f& pos) noexcept
{
	std::vector<Piece> allies = piece.color == sf::Color::Black ? black_pieces : white_pieces;
	const std::function<bool(const Piece&)> callback = [&pos](const Piece& pPos) -> bool { return pPos.position == pos; };
	return game::VectorContainsValue(allies, callback);
}

// Verifies if the occupied position is the position of an enemy
static bool IsPositionFilledByEnemy(const Piece& piece, const sf::Vector2f& pos) noexcept
{
	std::vector<Piece> enemies = piece.color == sf::Color::White ? black_pieces : white_pieces;
	const std::function<bool(const Piece&)> callback = [&pos](const Piece& pPos) -> bool { return pPos.position == pos; };
	return game::VectorContainsValue(enemies, callback);
}

std::vector<sf::Vector2f> game::CalculatePawnMoves(const Piece& piece) noexcept
{
	const float it = piece.color == sf::Color::Black ? 100.f : -100.f;
	std::vector<sf::Vector2f> positions;

	if ((piece.position.y > minpos || it > minpos) && (piece.position.y < maxpos || it < maxpos)) {
		sf::Vector2f next = { piece.position.x, piece.position.y + it };

		if (!game::IsPositionOccupied(next)) {
			positions.push_back(next);

			next.y += it;
			if (piece.position.y == 100.f || piece.position.y == 600.f && !IsPositionFilledByAlly(piece, next))
				positions.push_back({ piece.position.x, piece.position.y + it * 2 });
		}

		// TODO: Implementar captura "en-passant"

		const sf::Vector2f upLeft = { piece.position.x - it, piece.position.y + it };
		const sf::Vector2f upRight = { piece.position.x + it, piece.position.y + it };

		if (piece.position.x < maxpos && game::IsPositionOccupied(upLeft) && !IsPositionFilledByAlly(piece, upLeft))
			positions.push_back(upLeft);

		if (piece.position.x > minpos && game::IsPositionOccupied(upRight) && !IsPositionFilledByAlly(piece, upRight))
			positions.push_back(upRight);
	}

	return positions;
}

std::vector<sf::Vector2f> game::CalculateRookMoves(const Piece& piece) noexcept
{
	std::vector<sf::Vector2f> positions;

	for (float down = piece.position.y + 100.f; down <= maxpos; down += 100.f) {
		if (game::IsPositionOccupied({ piece.position.x, down })) {
			if (IsPositionFilledByEnemy(piece, { piece.position.x, down }))
				positions.push_back({ piece.position.x, down });

			break;
		};

		positions.push_back({ piece.position.x, down });
	}

	for (float up = piece.position.y - 100.f; up >= minpos; up -= 100.f) {
		if (game::IsPositionOccupied({ piece.position.x, up })) {
			if (IsPositionFilledByEnemy(piece, { piece.position.x, up }))
				positions.push_back({ piece.position.x, up });

			break;
		};

		positions.push_back({ piece.position.x, up });
	}

	for (float left = piece.position.x - 100.f; left >= minpos; left -= 100.f) {
		if (game::IsPositionOccupied({ left, piece.position.y })) {
			if (IsPositionFilledByEnemy(piece, { left, piece.position.y }))
				positions.push_back({ left, piece.position.y });

			break;
		}

		positions.push_back({ left, piece.position.y });
	}

	for (float right = piece.position.x + 100.f; right <= maxpos; right += 100.f) {
		if (game::IsPositionOccupied({ right, piece.position.y })) {
			if (IsPositionFilledByEnemy(piece, { right, piece.position.y }))
				positions.push_back({ right, piece.position.y });

			break;
		}

		positions.push_back({ right, piece.position.y });
	}

	return positions;
}

std::vector<sf::Vector2f> game::CalculateKnightMoves(const Piece& piece) noexcept
{
	std::vector<sf::Vector2f> positions;

	if (piece.position.x - 300.f >= minpos) {
		if (piece.position.y + 100.f <= maxpos && !IsPositionFilledByAlly(piece, { piece.position.x - 300.f, piece.position.y + 100.f }))
			positions.push_back({ piece.position.x - 300.f, piece.position.y + 100.f });

		if (piece.position.y - 100.f >= minpos && !IsPositionFilledByAlly(piece, { piece.position.x - 300.f, piece.position.y - 100.f }))
			positions.push_back({ piece.position.x - 300.f, piece.position.y - 100.f });
	}

	if (piece.position.x + 300.f <= maxpos) {
		if (piece.position.y + 100.f <= maxpos && !IsPositionFilledByAlly(piece, { piece.position.x + 300.f, piece.position.y + 100.f }))
			positions.push_back({ piece.position.x + 300.f, piece.position.y + 100.f });

		if (piece.position.y - 100.f >= minpos && !IsPositionFilledByAlly(piece, { piece.position.x + 300.f, piece.position.y - 100.f }))
			positions.push_back({ piece.position.x + 300.f, piece.position.y - 100.f });
	}

	if (piece.position.y - 300.f >= minpos) {
		if (piece.position.x + 100.f <= maxpos && !IsPositionFilledByAlly(piece, { piece.position.x + 100.f, piece.position.y - 300.f }))
			positions.push_back({ piece.position.x + 100.f, piece.position.y - 300.f });

		if (piece.position.x - 100.f >= minpos && !IsPositionFilledByAlly(piece, { piece.position.x - 100.f, piece.position.y - 300.f }))
			positions.push_back({ piece.position.x - 100.f, piece.position.y - 300.f });
	}

	if (piece.position.y + 300.f >= minpos) {
		if (piece.position.x + 100.f <= maxpos && !IsPositionFilledByAlly(piece, { piece.position.x + 100.f, piece.position.y + 300.f }))
			positions.push_back({ piece.position.x + 100.f, piece.position.y + 300.f });

		if (piece.position.x - 100.f >= minpos && !IsPositionFilledByAlly(piece, { piece.position.x - 100.f, piece.position.y + 300.f }))
			positions.push_back({ piece.position.x - 100.f, piece.position.y + 300.f });
	}


	return positions;
}

std::vector<sf::Vector2f> game::CalculateBishopMoves(const Piece& piece) noexcept
{
	std::vector<sf::Vector2f> positions;

	for (sf::Vector2f upL = piece.position; upL.x > minpos && upL.y > minpos; upL.x -= 100.f, upL.y -= 100.f) {
		if (game::IsPositionOccupied({ upL.x - 100.f, upL.y - 100.f })) {
			if (IsPositionFilledByEnemy(piece, { upL.x - 100.f, upL.y - 100.f }))
				positions.push_back({ upL.x - 100.f, upL.y - 100.f });

			break;
		}

		positions.push_back({ upL.x - 100.f, upL.y - 100.f });
	}

	for (sf::Vector2f upR = piece.position; upR.x < maxpos && upR.y > minpos; upR.x += 100.f, upR.y -= 100.f) {
		if (game::IsPositionOccupied({ upR.x + 100.f, upR.y - 100.f })) {
			if (IsPositionFilledByEnemy(piece, { upR.x + 100.f, upR.y - 100.f }))
				positions.push_back({ upR.x + 100.f, upR.y - 100.f });

			break;
		}

		positions.push_back({ upR.x + 100.f, upR.y - 100.f });
	}

	for (sf::Vector2f downL = piece.position; downL.x > minpos && downL.y < maxpos; downL.x -= 100.f, downL.y += 100.f) {
		if (game::IsPositionOccupied({ downL.x - 100.f, downL.y + 100.f })) {
			if (IsPositionFilledByEnemy(piece, { downL.x - 100.f, downL.y + 100.f }))
				positions.push_back({ downL.x - 100.f, downL.y + 100.f });

			break;
		}

		positions.push_back({ downL.x - 100.f, downL.y + 100.f });
	}

	for (sf::Vector2f downR = piece.position; downR.x < maxpos && downR.y < maxpos; downR.x += 100.f, downR.y += 100.f) {
		if (game::IsPositionOccupied({ downR.x + 100.f, downR.y + 100.f })) {
			if (IsPositionFilledByEnemy(piece, { downR.x + 100.f, downR.y + 100.f }))
				positions.push_back({ downR.x + 100.f, downR.y + 100.f });
			
			break;
		}
		
		positions.push_back({ downR.x + 100.f, downR.y + 100.f });
	}

	return positions;
}

std::vector<sf::Vector2f> game::CalculateQueenMoves(const Piece& piece) noexcept
{
	std::vector<sf::Vector2f> positions;

	std::vector<sf::Vector2f> rookPositions = game::CalculateRookMoves(piece);
	std::vector<sf::Vector2f> bishopPositions = game::CalculateBishopMoves(piece);

	positions.insert(positions.end(), rookPositions.begin(), rookPositions.end());
	positions.insert(positions.end(), bishopPositions.begin(), bishopPositions.end());

	return positions;
}

std::vector<sf::Vector2f> game::CalculateKingMoves(const Piece& piece) noexcept
{
	std::vector<sf::Vector2f> positions;

	sf::Vector2f up = { piece.position.x, piece.position.y - 100.f };
	sf::Vector2f down = { piece.position.x, piece.position.y + 100.f };
	sf::Vector2f left = { piece.position.x - 100.f, piece.position.y };
	sf::Vector2f right = { piece.position.x + 100.f, piece.position.y };
	sf::Vector2f upL = { piece.position.x - 100.f, piece.position.y - 100.f };
	sf::Vector2f upR = { piece.position.x + 100.f, piece.position.y - 100.f };
	sf::Vector2f downL = { piece.position.x - 100.f, piece.position.y + 100.f };
	sf::Vector2f downR = { piece.position.x + 100.f, piece.position.y + 100.f };

	if (piece.position.y > minpos && !IsPositionFilledByAlly(piece, up))
		positions.push_back(up);

	if (piece.position.y < maxpos && !IsPositionFilledByAlly(piece, down))
		positions.push_back(down);

	if (piece.position.x > minpos && !IsPositionFilledByAlly(piece, left))
		positions.push_back(left);

	if (piece.position.x < maxpos && !IsPositionFilledByAlly(piece, right))
		positions.push_back(right);

	if (piece.position.y > minpos && piece.position.x > minpos && !IsPositionFilledByAlly(piece, upL))
		positions.push_back(upL);

	if (piece.position.y > minpos && piece.position.x < maxpos && !IsPositionFilledByAlly(piece, upR))
		positions.push_back(upR);

	if (piece.position.y < maxpos && piece.position.x > minpos && !IsPositionFilledByAlly(piece, downL))
		positions.push_back(downL);

	if (piece.position.y < maxpos && piece.position.x < maxpos && !IsPositionFilledByAlly(piece, downR))
		positions.push_back(downR);

	return positions;
}

std::vector<sf::Vector2f> game::CalculatePieceMoves(const Piece& piece) noexcept
{
	switch (piece.type) {
	case Pawn:
		return CalculatePawnMoves(piece);

	case Rook:
		return CalculateRookMoves(piece);

	case Knight:
		return CalculateKnightMoves(piece);

	case Bishop:
		return CalculateBishopMoves(piece);

	case Queen:
		return CalculateQueenMoves(piece);

	case King:
	default:
		return CalculateKingMoves(piece);
	}
}