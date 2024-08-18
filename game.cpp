#include "game.h"
#include <cmath>

using namespace game;

sf::RenderWindow game::window = sf::RenderWindow(
	sf::VideoMode(window_wh, window_wh),
	"Chessboard", sf::Style::Titlebar | sf::Style::Close);

sf::Vector2f game::selected_position = sf::Vector2f(-1.f, -1.f); // Initilize with an invalid position

void game::WatchEvents() noexcept
{
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			double x = floor(abs(pos.x) / 100), y = floor(abs(pos.y) / 100);

			selected_position = sf::Vector2f((float)x * 100.f, (float)y * 100.f);
		}
	}
}

inline static bool IsPieceSelected() noexcept
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
		&& selected_position.x >= 0
		&& selected_position.y >= 0;
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

			square.setPosition(i * 100.0f, j * 100.0f);
			window.draw(square);
		}
	}

	if (IsPieceSelected()) {
		sf::RectangleShape selected(sf::Vector2f(100.0f, 100.0f));
		selected.setFillColor(sf::Color::Red);
		selected.setPosition(selected_position);
		window.draw(selected);
	}
}

void game::Run()
{
	game::LoadPieces();

	sf::Texture texture;
	texture.loadFromFile("..\\..\\..\\assets\\black_bishop.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(
		100.0f / sprite.getLocalBounds().width,
		100.0f / sprite.getLocalBounds().height
	);

	while (window.isOpen()) {
		window.clear();
		
		game::WatchEvents();
		game::DrawBoard();

		for (const Piece& piece : white_pieces) {
			texture.loadFromFile(game::GetTextureFilename(piece.type, sf::Color::White));
			sprite.setPosition(piece.position);
			window.draw(sprite);
		}

		for (const Piece& piece : black_pieces) {
			texture.loadFromFile(game::GetTextureFilename(piece.type, sf::Color::Black));
			sprite.setPosition(piece.position);
			window.draw(sprite);
		}

		// TODO: Move black pieces using ai

		window.display();
	}
}
