#pragma once

#include <ctime>
#include <vector>
#include "piece.h"

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
}