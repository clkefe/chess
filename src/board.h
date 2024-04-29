#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const  sf::Color COLOR_GREEN = {sf::Color(124, 148, 93)};
const sf::Color COLOR_WHITE =  {sf::Color(238,238,213)};

class Board {
    sf::RenderWindow &m_window;

    // This will be rendered the last to ensure that is on top of everything else. Serves as a queue in some sense.
    sf::Sprite selectedPieceSprite;

public:
    int board[64]; // Each index stores the piece in binary (first 3 bits -> type, last 2 bits -> color)
    int selectedPieceIndex;
    int colorToMove;

    explicit Board(sf::RenderWindow &window);

    void drawBackground();
    void drawPieces();

    void grabPiece();
    void releasePiece();
    void resetSelectedPiece();

    int getHoveredSquareIndex() const;

    void loadFromFEN(std::string const &FEN);
};

#endif //BOARD_H
