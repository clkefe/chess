#include "piece.h"
#include "texture_manager.h"

const std::map<char, int> Piece::pieceCharToValue = {
    { 'K', Piece::White | Piece::King },
    { 'P', Piece::White | Piece::Pawn },
    { 'N', Piece::White | Piece::Knight },
    { 'B', Piece::White | Piece::Bishop },
    { 'R', Piece::White | Piece::Rook },
    { 'Q', Piece::White | Piece::Queen },

    { 'k', Piece::Black | Piece::King },
    { 'p', Piece::Black | Piece::Pawn },
    { 'n', Piece::Black | Piece::Knight },
    { 'b', Piece::Black | Piece::Bishop },
    { 'r', Piece::Black | Piece::Rook },
    { 'q', Piece::Black | Piece::Queen },
};

void Piece::loadPieceTextures() {
    TextureManager::loadTexture(Piece::White | Piece::King, "src/images/pieces/white/K.png");
    TextureManager::loadTexture(Piece::White | Piece::Pawn, "src/images/pieces/white/P.png");
    TextureManager::loadTexture(Piece::White | Piece::Knight, "src/images/pieces/white/N.png");
    TextureManager::loadTexture(Piece::White | Piece::Bishop, "src/images/pieces/white/B.png");
    TextureManager::loadTexture(Piece::White | Piece::Rook, "src/images/pieces/white/R.png");
    TextureManager::loadTexture(Piece::White | Piece::Queen, "src/images/pieces/white/Q.png");

    TextureManager::loadTexture(Piece::Black | Piece::King, "src/images/pieces/black/k.png");
    TextureManager::loadTexture(Piece::Black | Piece::Pawn, "src/images/pieces/black/p.png");
    TextureManager::loadTexture(Piece::Black | Piece::Knight, "src/images/pieces/black/n.png");
    TextureManager::loadTexture(Piece::Black | Piece::Bishop, "src/images/pieces/black/b.png");
    TextureManager::loadTexture(Piece::Black | Piece::Rook, "src/images/pieces/black/r.png");
    TextureManager::loadTexture(Piece::Black | Piece::Queen, "src/images/pieces/black/q.png");
}
