#include "board.h"
#include "piece.h"

int main() {
    auto window = sf::RenderWindow{ { 800, 800 }, "Chess Game",  sf::Style::Close};
    window.setFramerateLimit(144);

    Board board{window};
    Piece::loadPieceTextures();

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(board.selectedPieceIndex != -1) {
                        board.releasePiece();
                        continue;
                    }

                    board.grabPiece();
                }
            }
        }

        window.clear();

        board.drawBackground();
        board.drawPieces();

        window.display();
    }
}