#include "board.h"
#include "event_handler.h"
#include "piece.h"

int main() {
    auto window = sf::RenderWindow{ { 800, 800 }, "Chess Game",  sf::Style::Close};
    window.setFramerateLimit(144);

    Board board{window};
    Piece::loadPieceTextures();

    EventHandler eventHandler(window, board);

    while (window.isOpen()) {
        eventHandler.listen();

        window.clear();

        board.drawBackground();
        board.drawPieces();

        window.display();
    }
}