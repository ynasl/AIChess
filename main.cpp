#include <SFML/Graphics.hpp>
#include "chess.h"
#include "ai.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Caesar's Chess");
	
	sf::Image board_image;
	board_image.loadFromFile("image\\board.png");

	sf::Texture board_texture;
	board_texture.loadFromImage(board_image);

	sf::Sprite board_sprite;
	board_sprite.setTexture(board_texture);
	board_sprite.setPosition(0, 0);

	sf::Image pieces_image;
	pieces_image.loadFromFile("image\\pieces.png");

	sf::Texture pieces_texture;
	pieces_texture.loadFromImage(pieces_image);

	sf::Sprite pieces_sprite;
	pieces_sprite.setTexture(pieces_texture);

	pieces_sprite.setScale(0.3, 0.3);

	Chess game;

	int move_count = 0;
	std::string move = "";

	while (window.isOpen()) {

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(board_sprite);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (game.chessBoard[i][j] == 'P') {
					pieces_sprite.setTextureRect(sf::IntRect(1702, 27, 182, 237));
					pieces_sprite.setPosition(20 + j * 100, 20 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'p') {
					pieces_sprite.setTextureRect(sf::IntRect(1702, 360, 182, 237));
					pieces_sprite.setPosition(20 + j * 100, 20 + i * 100);
					window.draw(pieces_sprite);
				}

				if (game.chessBoard[i][j] == 'R') {
					pieces_sprite.setTextureRect(sf::IntRect(1358, 27, 211, 233));
					pieces_sprite.setPosition(20 + j * 100, 27 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'r') {
					pieces_sprite.setTextureRect(sf::IntRect(1358, 360, 211, 233));
					pieces_sprite.setPosition(20 + j * 100, 27 + i * 100);
					window.draw(pieces_sprite);
				}

				if (game.chessBoard[i][j] == 'N') {
					pieces_sprite.setTextureRect(sf::IntRect(1003, 12, 247, 248));
					pieces_sprite.setPosition(10 + j * 100, 22 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'n') {
					pieces_sprite.setTextureRect(sf::IntRect(1003, 345, 247, 248));
					pieces_sprite.setPosition(10 + j * 100, 22 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'B') {
					pieces_sprite.setTextureRect(sf::IntRect(669, 1, 256, 258));
					pieces_sprite.setPosition(10 + j * 100, 20 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'b') {
					pieces_sprite.setTextureRect(sf::IntRect(669, 334, 256, 258));
					pieces_sprite.setPosition(10 + j * 100, 17 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'Q') {
					pieces_sprite.setTextureRect(sf::IntRect(321, 1, 284, 261));
					pieces_sprite.setPosition(5 + j * 100, 17 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'q') {
					pieces_sprite.setTextureRect(sf::IntRect(321, 338, 284, 261));
					pieces_sprite.setPosition(5 + j * 100, 20 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'K') {
					pieces_sprite.setTextureRect(sf::IntRect(1, 4, 261, 258));
					pieces_sprite.setPosition(10 + j * 100, 20 + i * 100);
					window.draw(pieces_sprite);
				}
				if (game.chessBoard[i][j] == 'k') {
					pieces_sprite.setTextureRect(sf::IntRect(1, 338, 261, 258));
					pieces_sprite.setPosition(10 + j * 100, 20 + i * 100);
					window.draw(pieces_sprite);
				}

			}
		}
		window.display();

		if (move_count % 2 == 0) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left && move.size() == 0)
					move = move + char(pos.x / 100 + 97) + char(56 - pos.y / 100);
				if (event.key.code == sf::Mouse::Right && move.size() == 2)
					move = move + char(pos.x / 100 + 97) + char(56 - pos.y / 100);


				if (move.size() == 4) {
					try {
						game.makeMove(move);
						move_count++;
						move = "";
					}
					catch (std::exception& ex) {
						move = "";
					}
				}
			}
		}

		else {
			move = botMove(game);
			game.makeMove(move);
			move_count++;
			move = "";
		}

	}

	return 0;
}
