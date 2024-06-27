#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <SFML/Graphics.hpp>
#include "../piece.h"

class GraphicsManager {
    const sf::Color COLOR_GREEN = {sf::Color(124, 148, 93)};
    const sf::Color COLOR_WHITE = {sf::Color(238, 238, 213)};

    sf::RenderWindow &m_window;
    Piece (&m_square)[64];

public:
    explicit GraphicsManager(sf::RenderWindow &window, Piece (&square)[64]);
    ~GraphicsManager() = default;

    void draw();

    void drawBackground();
    void drawPieces();
};


#endif //GRAPHICSMANAGER_H
