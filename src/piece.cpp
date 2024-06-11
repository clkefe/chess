#include "piece.h"

#include "PieceManager.h"

Piece::Piece(const int identifier) : m_identifier(identifier) {}

int Piece::getColor() const {
    return (m_identifier & PieceManager::PIECE_COLOR_MASK);
}

int Piece::getType() const {
    return m_identifier & PieceManager::PIECE_TYPE_MASK;
}
