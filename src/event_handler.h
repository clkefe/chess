#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "board.h"
#include <SFML/Graphics.hpp>

class EventHandler {
    sf::RenderWindow &m_window;
    Board            &m_board;

    void onClose() const;
    void onMouseClick(const sf::Event& event) const;

public:
    EventHandler(sf::RenderWindow &window, Board &board);
    ~EventHandler() = default;

    void listen() const;
};

#endif //EVENT_HANDLER_H
