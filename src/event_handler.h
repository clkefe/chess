#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SFML/Graphics.hpp>
#include "board.h"

class EventHandler {
    sf::RenderWindow &m_window;
    Board &m_board;

    void onClose();

    void onMouseClick(const sf::Event &event);

public:
    EventHandler(sf::RenderWindow &window, Board &board) : m_window(window), m_board(board) {
    }

    void listen();
};

#endif //EVENT_HANDLER_H
