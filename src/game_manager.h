#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Graphics/GraphicsManager.h"
#include "event_handler.h"
#include "piece.h"

#include <iostream>

const sf::VideoMode GAME_RES = {800, 800};
const std::string GAME_TITLE = "Chess Game";

class GameManager {
    sf::RenderWindow m_window{GAME_RES, GAME_TITLE, sf::Style::Close};

    EventHandler m_eventHandler;
    GraphicsManager m_graphicsManager;

    Piece square[64]{};
    int selectedPieceIndex{-1};
    int colorToMove{};

    void loop();

public:
    GameManager();

    ~GameManager() = default;

    void loadFromFEN(std::string const &FEN);
};

#endif //GAME_MANAGER_H
