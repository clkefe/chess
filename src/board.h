#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

const sf::Color COLOR_GREEN = {sf::Color(124, 148, 93)};
const sf::Color COLOR_WHITE = {sf::Color(238, 238, 213)};

class Board {
    // This will be rendered the last to ensure that is on top of everything else.
    sf::Sprite selectedPieceSprite;

    sf::RenderWindow &m_window;

public:
    explicit Board(sf::RenderWindow &window);

    void drawBackground();

    // void drawLegalMovesHighlight();

    // void drawPieces();

    // void grabPiece();
    //
    // void placePiece();
    //
    // void resetSelectedPiece();
    //
    // int getHoveredSquareIndex() const;
};

#endif //BOARD_H
