#pragma once

#include <ctime>
#include <vector>
#include <functional>

#define FontPath "..\\..\\..\\assets\\font.ttf"

#define WhitePawnPath "..\\..\\..\\assets\\white_pawn.png"
#define WhiteRookPath "..\\..\\..\\assets\\white_rook.png"
#define WhiteKnightPath "..\\..\\..\\assets\\white_knight.png"
#define WhiteBishopPath "..\\..\\..\\assets\\white_bishop.png"
#define WhiteQueenPath "..\\..\\..\\assets\\white_queen.png"
#define WhiteKingPath "..\\..\\..\\assets\\white_king.png"

#define BlackPawnPath "..\\..\\..\\assets\\black_pawn.png"
#define BlackRookPath "..\\..\\..\\assets\\black_rook.png"
#define BlackKnightPath "..\\..\\..\\assets\\black_knight.png"
#define BlackBishopPath "..\\..\\..\\assets\\black_bishop.png"
#define BlackQueenPath "..\\..\\..\\assets\\black_queen.png"
#define BlackKingPath "..\\..\\..\\assets\\black_king.png"

namespace game
{
	typedef unsigned int uint;

	template <typename _Ty>
	uint GetRandomNumber(std::vector<_Ty>& vec) noexcept
	{
		std::srand(static_cast<unsigned>(std::time(0)));
		uint randomIndex = std::rand() % vec.size();
		return randomIndex;
	}

	template <typename _Ty>
	bool VectorContainsValue(std::vector<_Ty>& vec, std::function<bool(const _Ty&)> callback)
	{
		return vec.end() != std::find_if(vec.begin(), vec.end(), callback);
	}
}