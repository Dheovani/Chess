#include <cstdlib>
#include <iostream>

#include "game.h"

int main(void)
{
	game::SWindow window = game::GetWindow();

	if (!window) {
		std::cout << "Could not generate simulation's window!!" << std::endl;
		return EXIT_FAILURE;
	}

	game::Run(window);

	if (window && window->isOpen())
		window->close();

	return EXIT_SUCCESS;
}