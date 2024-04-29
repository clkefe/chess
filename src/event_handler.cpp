#include "event_handler.h"

EventHandler::EventHandler(sf::RenderWindow &window, Board &board) : m_window(window), m_board(board) {}

void EventHandler::listen() const {
    for (auto event = sf::Event{}; m_window.pollEvent(event);) {
        switch(event.type) {
            case sf::Event::Closed:
                this->onClose();
                break;
            case sf::Event::MouseButtonPressed:
                this->onMouseClick(event);
                break;
            default:
                break;
        }
    }
}

void EventHandler::onClose() const {
    m_window.close();
}

void EventHandler::onMouseClick(const sf::Event &event) const {
    if(event.mouseButton.button == sf::Mouse::Left) {
        if(m_board.selectedPieceIndex == -1) {
            m_board.grabPiece();
        } else {
            m_board.releasePiece();
        }
    }
}
