#include <cstdlib>
#include <iostream>

#include "game.h"

int main(void)
{
	game::Run();

	if (game::window.isOpen())
		game::window.close();

	return EXIT_SUCCESS;
}