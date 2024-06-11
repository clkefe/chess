#include "event_handler.h"

void EventHandler::listen() {
    for (auto event = sf::Event{}; m_window.pollEvent(event);) {
        switch (event.type) {
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

void EventHandler::onClose() {
    m_window.close();
}

void EventHandler::onMouseClick(const sf::Event &event) {
    // switch (event.mouseButton.button) {
    //     case sf::Mouse::Left:
    //         if (m_board.selectedPieceIndex == -1) {
    //             m_board.grabPiece();
    //         } else {
    //             m_board.placePiece();
    //         }
    //         break;
    //     case sf::Mouse::Right:
    //         m_board.resetSelectedPiece();
    //         break;
    //     default:
    //         break;
    // }
}
