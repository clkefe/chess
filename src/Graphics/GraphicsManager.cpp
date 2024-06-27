//
// Created by Efe Celik on 6/14/24.
//

#include "GraphicsManager.h"

#include <iostream>

#include "../PieceManager.h"
#include "../texture_manager.h"

GraphicsManager::GraphicsManager(sf::RenderWindow &window, Piece (&square)[64]): m_window(window), m_square(square) {}

void GraphicsManager::draw() {
    m_window.clear();

    drawBackground();
    // drawLegalMovesHighlight();
    drawPieces();

    m_window.display();
}


void GraphicsManager::drawBackground() {
    // We use 256 vertex because each quad needs 4 vertex, and there are 64 squares on a chess board (64*4=256).
    sf::VertexArray background(sf::Quads, 256);

    float pos_x{0};
    float pos_y{0};

    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            const int startingIndex = (rank * 8 + file) * 4; // Muliply by 4 because each quad has 4 vertex.

            background[startingIndex].position = sf::Vector2f(pos_x, pos_y + 100); // left-bottom
            background[startingIndex + 1].position = sf::Vector2f(pos_x, pos_y); // left-top
            background[startingIndex + 2].position = sf::Vector2f(pos_x + 100, pos_y); // right-top
            background[startingIndex + 3].position = sf::Vector2f(pos_x + 100, pos_y + 100); // right-bottom

            // Set the color of each vertex of each quad/square (each quad has 4 vertex).
            const sf::Color squareColor = (rank + file) % 2 == 0 ? COLOR_GREEN : COLOR_WHITE;
            for (int j = 0; j < 4; j++) {
                background[startingIndex + j].color = squareColor;
            }

            pos_x += 100.f;
        }

        pos_y += 100.f;
        pos_x = 0;
    }

    m_window.draw(background);
}

void GraphicsManager::drawPieces() {
    for (int i = 0; i < 64; i++) {
        if (const int pieceType = m_square[i].getIdentifier(); pieceType != PieceManager::None) {
            sf::Sprite sprite;
            sprite.setTexture(TextureManager::getTexture(pieceType));

            const int rank = i / 8;
            const int file = i % 8;

            const float pos_x = static_cast<float>(file) * 100;
            const float pos_y = static_cast<float>(rank) * 100;

            // Skip rendering the selected piece now. It will be rendered last so it is on the top.
            // if (i == selectedPieceIndex) {
            //     selectedPieceSprite = sprite;
            //     continue;
            // }

            sprite.setPosition(pos_x, pos_y);

            m_window.draw(sprite);
        }
    }

    // if (selectedPieceIndex != -1) {
    //     const float pos_x = static_cast<float>(sf::Mouse::getPosition(m_window).x) - 50;
    //     const float pos_y = static_cast<float>(sf::Mouse::getPosition(m_window).y) - 50;
    //
    //     selectedPieceSprite.setPosition(pos_x, pos_y);
    //     m_window.draw(selectedPieceSprite);
    // }
}
