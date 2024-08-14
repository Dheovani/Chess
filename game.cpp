#include "game.h"
#include <cmath>
#include <SFML/OpenGL.hpp>

// TODO: Delete
#include <iostream>

using namespace game;

RenderWindow game::window = RenderWindow(
	sf::VideoMode(window_wh, window_wh),
	"Chessboard", sf::Style::Titlebar | sf::Style::Close);

sf::Vector2f game::selected_position = sf::Vector2f(0.f, 0.f);

static bool IsPieceSelected(int x, int y)
{
	bool is_white_piece_position = white_pieces.end() != std::find_if(white_pieces.begin(), white_pieces.end(),
		[](const Piece& piece) -> bool {
			return piece.position == selected_position;
		});

	bool is_black_piece_position = black_pieces.end() != std::find_if(black_pieces.begin(), black_pieces.end(),
		[](const Piece& piece) -> bool {
			return piece.position == selected_position;
		});

	return (is_white_piece_position || is_black_piece_position)
		&& selected_position.x && selected_position.x == x * 100.0f
		&& selected_position.y && selected_position.y == y * 100.0f;
}

void game::DrawBoard() noexcept
{
	sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2 == 0)
				square.setFillColor(sf::Color::White);
			else
				square.setFillColor(sf::Color::Black);

			if (IsPieceSelected(i, j)) {
				square.setOutlineColor(sf::Color::Red);
				square.setOutlineThickness(1.5f);
			}
			else
				square.setOutlineThickness(0);

			square.setPosition(i * 100.0f, j * 100.0f);
			window.draw(square);
		}
	}
}

static sf::Sprite GetShape(sf::Vector2f pos)
{
	sf::Texture texture;
	texture.loadFromFile("..\\..\\..\\assets\\pawn.png");

	sf::Sprite sprite;
	sprite.setColor(sf::Color::Green);
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sprite.setScale(
		100.0f / sprite.getLocalBounds().width / 2,
		100.0f / sprite.getLocalBounds().height / 2
	);

	return sprite;
}

void game::Run()
{
	game::LoadPieces();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				float x = (float)floor(abs(pos.x) / 100), y = (float)floor(abs(pos.y) / 100);

				selected_position = sf::Vector2f(x * 100.f, y * 100.f);
			}
		}

		window.clear();
		game::DrawBoard();
		
		for (Piece& piece : white_pieces)
			window.draw(GetShape(piece.position));

		for (Piece& piece : black_pieces)
			window.draw(GetShape(piece.position));

		// TODO: Move black pieces using ai

		window.display();
	}
}
