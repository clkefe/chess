#include "board.h"

// #include "piece.h"
#include "texture_manager.h"

Board::Board(sf::RenderWindow &window): m_window(window) {}

void Board::drawBackground() {
    // We use 256 vertex because each quad needs 4 vertex, and there are 64 squares on a chess board (64*4=256).
    sf::VertexArray background(sf::Quads, 256);

    float pos_x{0};
    float pos_y{0};

    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            const int startingIndex = (rank * 8 + file) * 4; // Muliply by 4 because each quad has 4 vertex.

            background[startingIndex].position = sf::Vector2f(pos_x, pos_y + 100); // left-bottom
            background[startingIndex + 1].position = sf::Vector2f(pos_x, pos_y); // left-top
            background[startingIndex + 2].position = sf::Vector2f(pos_x + 100, pos_y); // right-top
            background[startingIndex + 3].position = sf::Vector2f(pos_x + 100, pos_y + 100); // right-bottom

            // Set the color of each vertex of each quad/square (each quad has 4 vertex).
            const sf::Color squareColor = (rank + file) % 2 == 0 ? COLOR_GREEN : COLOR_WHITE;
            for (int j = 0; j < 4; j++) {
                background[startingIndex + j].color = squareColor;
            }

            pos_x += 100.f;
        }

        pos_y += 100.f;
        pos_x = 0;
    }

    m_window.draw(background);
}

// void Board::drawLegalMovesHighlight() {
//     if (Piece::legalMoves.empty()) {
//         return;
//     }
//
//     const int numberOfVertex = Piece::legalMoves.size() * 4;
//     sf::VertexArray highlights(sf::Quads, numberOfVertex);
//
//     for (int i = 0; i < Piece::legalMoves.size(); ++i) {
//         int legalMove = Piece::legalMoves[i];
//         const int rank = legalMove / 8;
//         const int file = legalMove % 8;
//
//         const float pos_x = static_cast<float>(file) * 100;
//         const float pos_y = static_cast<float>(rank) * 100;
//
//         int startingIndex = i * 4;
//
//         highlights[startingIndex].position = sf::Vector2f(pos_x + 25, pos_y + 75); // left-bottom
//         highlights[startingIndex + 1].position = sf::Vector2f(pos_x + 25, pos_y + 25); // left-top
//         highlights[startingIndex + 2].position = sf::Vector2f(pos_x + 75, pos_y + 25); // right-top
//         highlights[startingIndex + 3].position = sf::Vector2f(pos_x + 75, pos_y + 75); // right-bottom
//
//         for (int j = 0; j < 4; j++) {
//             highlights[startingIndex + j].color = sf::Color(0, 230, 250, 120);
//         }
//     }
//
//
//     m_window.draw(highlights);
// }


// void Board::grabPiece() {
//     const int howeredSquareIndex = getHoveredSquareIndex();
//     const int selectedPiece = square[howeredSquareIndex];
//
//     if (selectedPiece == Piece::None) {
//         return;
//     }
//
//     if (!Piece::isColor(selectedPiece, colorToMove)) {
//         return;
//     }
//
//     selectedPieceIndex = howeredSquareIndex;
//     Piece::generateMoves(selectedPiece, selectedPieceIndex, square);
// }
//
// void Board::placePiece() {
//     const int releasedSquareIndex = getHoveredSquareIndex();
//     const int selectedPiece = square[selectedPieceIndex];
//
//     if (selectedPieceIndex == releasedSquareIndex) {
//         resetSelectedPiece();
//         return;
//     }
//
//     for (int i{0}; i < Piece::legalMoves.size(); i++) {
//         if (releasedSquareIndex == Piece::legalMoves.at(i)) {
//             square[selectedPieceIndex] = Piece::None;
//             square[releasedSquareIndex] = selectedPiece;
//
//             colorToMove = colorToMove == Piece::White ? Piece::Black : Piece::White;
//             resetSelectedPiece();
//         }
//     }
// }
//
// void Board::resetSelectedPiece() {
//     selectedPieceIndex = -1;
//     selectedPieceSprite = {};
//     Piece::legalMoves.clear();
// }

// int Board::getHoveredSquareIndex() const {
//     const int mousePosX = sf::Mouse::getPosition(m_window).x;
//     const int mousePosY = sf::Mouse::getPosition(m_window).y;
//
//     const int mouseOnRank = mousePosY / 100;
//     const int mouseOnFile = mousePosX / 100;
//
//     return mouseOnRank * 8 + mouseOnFile;
// }
