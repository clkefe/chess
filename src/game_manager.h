#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "board.h"
#include "event_handler.h"

#include <iostream>

#include "piece.h"

const sf::VideoMode GAME_RES = {800, 800};
const std::string GAME_TITLE = "Chess Game";

class GameManager {
    EventHandler m_eventHandler;
    sf::RenderWindow m_window;
    Board m_board;

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
