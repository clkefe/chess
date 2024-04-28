#include "board.h"

#include "piece.h"
#include "texture_manager.h"

Board::Board(sf::RenderWindow& window) : m_window{window}, board{} {
    loadFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::drawBackground() {
    // We use 256 vertex because each quad needs 4 vertex, and there are 64 squares on a chess board (64*4=256).
    sf::VertexArray background(sf::Quads, 256);

    float pos_x{0};
    float pos_y{0};

    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            const int startingIndex = (rank * 8 + file) * 4; // Muliply by 4 because each quad has 4 vertex.

            background[startingIndex].position     = sf::Vector2f(pos_x,       pos_y + 100); // left-bottom
            background[startingIndex + 1].position = sf::Vector2f(pos_x,       pos_y      ); // left-top
            background[startingIndex + 2].position = sf::Vector2f(pos_x + 100, pos_y      ); // right-top
            background[startingIndex + 3].position = sf::Vector2f(pos_x + 100, pos_y + 100); // right-bottom

            // Set the color of each vertex of each quad/square (each quad has 4 vertex).
            const sf::Color squareColor = (rank + file) % 2 == 0 ? COLOR_GREEN : COLOR_WHITE;
            for(int j = 0; j < 4; j++) {
                background[startingIndex + j].color = squareColor;
            }

            pos_x += 100.f;
        }

        pos_y += 100.f;
        pos_x = 0;
    }

    m_window.draw(background);
}

void Board::drawPieces() {
        for(int i = 0; i < 64; i++) {
            if(board[i] != Piece::None) {
                const int piece = board[i];

                sf::Sprite sprite;
                sprite.setTexture(TextureManager::getTexture(piece));

                const int rank = i / 8;
                const int file = i % 8;

                const float pos_x = static_cast<float>(file) * 100;
                const float pos_y = static_cast<float>(rank) * 100;

                sprite.setPosition(pos_x, pos_y);

                m_window.draw(sprite);
            }
        }
}

void Board::loadFromFEN(const std::string &FEN) {
    const std::string piecePlacement = FEN.substr(0, FEN.find(' '));

    int rank{0};
    int file{0};

    for(char c : piecePlacement) {
        if(isdigit(c)) {
            const int numberOfEmptySquares = c - '0'; // char to int conversion
            file += numberOfEmptySquares;
        } else if(c == '/') {
            rank++;
            file = 0;
        } else {
            board[rank * 8 + file] = Piece::pieceCharToValue.at(c);
            file++;
        }
    }
}

