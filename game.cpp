#include "game.h"
#include <cmath>
#include "utils.h"
#include <functional>
#include "piece_movements.h"

using namespace game;

static const sf::Vector2f invalid_position = sf::Vector2f(-1.f, -1.f);

sf::RenderWindow game::window = sf::RenderWindow(
	sf::VideoMode(window_wh, window_wh),
	"Chessboard", sf::Style::Titlebar | sf::Style::Close);

sf::Vector2f game::selected_position = invalid_position; // Initilize with an invalid position

bool game::player_turn = true;

static void DrawGameOverScreen(const bool player_won)
{
	sf::RectangleShape background(sf::Vector2f(window.getSize()));
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font font;
	if (!font.loadFromFile(FontPath)) {
		return;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(player_won ? "You win!" : "You lose!");
	text.setCharacterSize(50);
	text.setFillColor(player_won ? sf::Color::White : sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setPosition(
		window.getSize().x / 2 - text.getGlobalBounds().width / 2,
		window.getSize().y / 2 - text.getGlobalBounds().height / 2
	);

	window.clear();
	window.draw(background);
	window.draw(text);
	window.display();
}

static int DrawPromotionOptions(const std::vector<std::string>& options)
{
	float spacing = 40.f;
	int selectedItemIndex = -1;
	unsigned int textSize = 30;

	sf::RectangleShape background(sf::Vector2f(window.getSize()));
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font font;
	if (!font.loadFromFile(FontPath)) {
		return selectedItemIndex;
	}

	while (window.isOpen() && selectedItemIndex == -1 && !options.empty()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				selectedItemIndex = event.key.code - 26;
			}
		}

		window.clear(sf::Color::Black);

		sf::Text text;
		text.setFont(font);
		text.setString("Type the value of the piece to promote your pawn:");
		text.setCharacterSize(textSize);
		text.setPosition(10.f, 10.f);
		text.setFillColor(sf::Color::White);
		window.draw(text);

		for (size_t i = 0; i < options.size(); ++i) {
			sf::Text text;
			text.setFont(font);
			text.setString(std::string{ options[i] + " (" + std::to_string(i) + ")" });
			text.setCharacterSize(textSize);
			text.setPosition(10.f, 100.f + i * spacing);

			if (i == selectedItemIndex) {
				text.setFillColor(sf::Color::Yellow);
				text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			else {
				text.setFillColor(sf::Color::White);
			}

			window.draw(text);
		}

		window.display();
	}

	return selectedItemIndex;
}

bool game::GameOver() noexcept
{
	const std::function<bool(const Piece&)> callback = [](const Piece& p) -> bool { return p.type == King; };
	const bool whiteKingIsAlive = game::VectorContainsValue(white_pieces, callback);
	const bool blackKingIsAlive = game::VectorContainsValue(black_pieces, callback);

	if (whiteKingIsAlive && !blackKingIsAlive) {
		DrawGameOverScreen(true);
		return true;
	}

	if (blackKingIsAlive && !whiteKingIsAlive) {
		DrawGameOverScreen(false);
		return true;
	}

	return false;
}

void game::PromotePawn(Piece& piece) noexcept
{
	std::vector<std::string> piecesToPromote;

	for (Piece& p : lost_pieces) {
		if (piece.color == p.color) {
			switch (p.type) {
			case Pawn: piecesToPromote.push_back("Pawn");
				break;
			case Rook: piecesToPromote.push_back("Rook");
				break;
			case Knight: piecesToPromote.push_back("Knight");
				break;
			case Bishop: piecesToPromote.push_back("Bishop");
				break;
			case Queen: piecesToPromote.push_back("Queen");
				break;
			case King: piecesToPromote.push_back("King");
				break;
			}
		}
	}

	int option = DrawPromotionOptions(piecesToPromote);
	std::string type = piecesToPromote[option].c_str();

	if (type == "Pawn")
		piece.type = Pawn;
	else if (type == "Rook")
		piece.type = Rook;
	else if (type == "Knight")
		piece.type = Knight;
	else if (type == "Bishop")
		piece.type = Bishop;
	else if (type == "Queen")
		piece.type = Queen;
}

void game::Move(Piece piece, sf::Vector2f newPos) noexcept
{
	std::vector<sf::Vector2f> validPositions = game::CalculatePieceMoves(piece);
	std::vector<Piece>& allies = piece.color == sf::Color::Black ? black_pieces : white_pieces;
	std::vector<Piece>& enemies = piece.color == sf::Color::White ? black_pieces : white_pieces;
	
	const std::function<bool(const sf::Vector2f&)> callback = [&newPos](const sf::Vector2f& pos) -> bool { return pos == newPos; };
	if (game::VectorContainsValue(validPositions, callback)) {
		enemies.erase(
			std::remove_if(enemies.begin(), enemies.end(),
				[&newPos](const Piece& p) -> bool {
					if (p.position == newPos) {
						lost_pieces.push_back(p);
						return true;
					}

					return false;
				}),
			enemies.end()
		);

		for (Piece& p : allies) {
			if (piece == p) {
				p.position = newPos;

				if (p.type == Pawn && (newPos.y == 0.f || newPos.y == 700.f)) {
					game::PromotePawn(p);
				}

				break;
			}
		}

		player_turn = false;
	}

	selected_position = invalid_position;
}

void game::MoveBlackPiece() noexcept
{
	size_t piece_n = game::GetRandomNumber(black_pieces);
	Piece& piece = black_pieces[piece_n];
	std::vector<sf::Vector2f> validPositions;

	while(validPositions.empty()) {
		piece_n = game::GetRandomNumber(black_pieces);
		piece = black_pieces[piece_n];
		validPositions = game::CalculatePieceMoves(piece);
	}

	size_t pos_n = game::GetRandomNumber(validPositions);
	game::Move(piece, validPositions[pos_n]);
	player_turn = true;
}

void game::WatchEvents() noexcept
{
	sf::Event event;

	std::function<bool(sf::Vector2f)> isInvalidPiece = [](sf::Vector2f pos) -> bool {
		const std::function<bool(const Piece&)> callback = [&pos](const Piece& pPos) -> bool { return pPos.position == pos; };
		return game::VectorContainsValue(black_pieces, callback);
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
		
		if (game::GameOver())
			continue;

		if (player_turn)
			game::WatchEvents();
		else
			game::MoveBlackPiece();

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

		window.display();
	}
}
