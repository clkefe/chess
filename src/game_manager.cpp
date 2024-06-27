#include "game_manager.h"

#include "event_handler.h"
#include "PieceManager.h"
#include "texture_manager.h"

GameManager::GameManager() : m_eventHandler(m_window), m_graphicsManager(m_window, square) {
    TextureManager::loadPieceTextures();

    loadFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    loop();
}

void GameManager::loop() {
    while (m_window.isOpen()) {
        m_eventHandler.listen();
        m_graphicsManager.draw();
    }
}

void GameManager::loadFromFEN(const std::string &FEN) {
    const std::string piecePlacement = FEN.substr(0, FEN.find(' '));

    std::string colorToMoveString = FEN.substr(FEN.find(' ') + 1, std::size(FEN));
    colorToMoveString = colorToMoveString.substr(0, colorToMoveString.find(' '));

    colorToMove = colorToMoveString == "w" ? PieceManager::White : PieceManager::Black;

    int rank{0};
    int file{0};

    for (char c: piecePlacement) {
        if (isdigit(c)) {
            const int numberOfEmptySquares = c - '0'; // char to int conversion
            file += numberOfEmptySquares;
        } else if (c == '/') {
            rank++;
            file = 0;
        } else {
            square[rank * 8 + file] = Piece(PieceManager::pieceCharToValue.at(c));
            file++;
        }
    }
}
