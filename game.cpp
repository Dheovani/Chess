#include "game.h"
#include <cmath>
#include <functional>
#include "piece_movements.h"

using namespace game;

static const sf::Vector2f invalid_position = sf::Vector2f(-1.f, -1.f);

sf::RenderWindow game::window = sf::RenderWindow(
	sf::VideoMode(window_wh, window_wh),
	"Chessboard", sf::Style::Titlebar | sf::Style::Close);

sf::Vector2f game::selected_position = invalid_position; // Initilize with an invalid position

bool game::player_turn = true;

void game::Move(Piece piece, sf::Vector2f newPos) noexcept
{
	std::vector<sf::Vector2f> validPositions = game::CalculatePieceMoves(piece);
	std::vector<Piece>& allies = piece.color == sf::Color::Black ? black_pieces : white_pieces;
	std::vector<Piece>& enemies = piece.color == sf::Color::White ? black_pieces : white_pieces;
	
	if (validPositions.end() != std::find_if(validPositions.begin(), validPositions.end(),
		[&newPos](sf::Vector2f pos) -> bool {
			return pos == newPos;
		}))
	{
		for (Piece& p : allies) {
			if (piece == p) {
				p.position = newPos;
			}
		}

		enemies.erase(
			std::remove_if(enemies.begin(), enemies.end(),
				[&newPos](const Piece& p) {
					return p.position == newPos;
				}),
			enemies.end()
		);

		selected_position = invalid_position;
		player_turn = false;
	}
}

void game::WatchEvents() noexcept
{
	sf::Event event;

	std::function<bool(sf::Vector2f)> isInvalidPiece = [](sf::Vector2f pos) -> bool {
		return black_pieces.end() != std::find_if(black_pieces.begin(), black_pieces.end(),
			[&pos](Piece& pPos) -> bool { return pPos.position == pos; });
	};

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			double x = floor(abs(pos.x) / 100), y = floor(abs(pos.y) / 100);
			sf::Vector2f mousePos = sf::Vector2f((float)x * 100.f, (float)y * 100.f);

			if (selected_position == invalid_position) {
				if (isInvalidPiece(mousePos)) // Can only select white pieces
					continue;

				selected_position = mousePos;
			}
			else {
				Piece piece = game::GetPieceByPosition(selected_position);
				game::Move(piece, mousePos);
			}
		}
	}
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

	if (game::IsPositionOccupied(selected_position)) {
		sf::RectangleShape selected(sf::Vector2f(100.0f, 100.0f));
		selected.setFillColor(sf::Color::Red);
		selected.setPosition(selected_position);
		window.draw(selected);

		Piece piece = game::GetPieceByPosition(selected_position);
		std::vector<sf::Vector2f> possibleMoves = game::CalculatePieceMoves(piece);

		for (sf::Vector2f pos : possibleMoves) {
			sf::RectangleShape rs(sf::Vector2f(100.0f, 100.0f));
			rs.setFillColor(sf::Color::Red);
			rs.setPosition(pos);
			window.draw(rs);
		}
	}
}

void game::Run()
{
	game::LoadPieces();

	sf::Texture texture;
	texture.loadFromFile(std::string(assets_dir_path) + "black_bishop.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(
		100.0f / sprite.getLocalBounds().width,
		100.0f / sprite.getLocalBounds().height
	);

	while (window.isOpen()) {
		window.clear();
		
		if (player_turn)
			game::WatchEvents();

		game::DrawBoard();

		for (const Piece& piece : white_pieces) {
			texture.loadFromFile(game::GetTextureFilename(piece));
			sprite.setPosition(piece.position);
			window.draw(sprite);
		}

		for (const Piece& piece : black_pieces) {
			texture.loadFromFile(game::GetTextureFilename(piece));
			sprite.setPosition(piece.position);
			window.draw(sprite);
		}

		// TODO: Encontrar uma forma de mover as peças negras
		// TODO: Atualizar o turno após mover as peças negras

		window.display();
	}
}
