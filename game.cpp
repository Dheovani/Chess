#include "game.h"
#include <SFML/OpenGL.hpp>

using namespace game;

void game::DisplayPieces() noexcept
{

}

void game::DrawBoard() noexcept
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2 == 0)
				glColor3f(1.0f, 1.0f, 1.0f);
			else
				glColor3f(0.0f, 0.0f, 0.0f);

			glVertex2f(i * 0.25f - 1.0f, j * 0.25f - 1.0f);
			glVertex2f((i + 1) * 0.25f - 1.0f, j * 0.25f - 1.0f);
			glVertex2f((i + 1) * 0.25f - 1.0f, (j + 1) * 0.25f - 1.0f);
			glVertex2f(i * 0.25f - 1.0f, (j + 1) * 0.25f - 1.0f);
		}
	}
}

SWindow game::GetWindow() noexcept
{
	auto window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(window_wh, window_wh), "Chessboard", sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);

	return window;
}

void game::Run(const SWindow& window)
{
	glEnable(GL_DEPTH_TEST);

	while (window->isOpen()) {
		sf::Event event;
		// TODO: Catch click event on player's turn
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_QUADS);
		
		DrawBoard();

		// TODO: Move black pieces using ai

		glEnd();
		window->display();
	}
}
