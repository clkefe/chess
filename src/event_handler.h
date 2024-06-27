#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SFML/Graphics.hpp>

class EventHandler {
    sf::RenderWindow &m_window;

    void onClose();

    void onMouseClick(const sf::Event &event);

public:
    explicit EventHandler(sf::RenderWindow &window) : m_window(window) {}

    void listen();
};

#endif //EVENT_HANDLER_H
