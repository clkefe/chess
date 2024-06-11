#include "texture_manager.h"

#include <iostream>
#include "piece.h"

std::map<int, sf::Texture> TextureManager::textures;

bool TextureManager::loadTexture(const int &piece, const std::string &filePath) {
    sf::Texture texture;

    if (!texture.loadFromFile(filePath)) {
        return false;
    }

    textures[piece] = texture;
    return true;
}

sf::Texture &TextureManager::getTexture(const int &piece) {
    return textures.at(piece);
}

void TextureManager::loadPieceTextures() {
    loadTexture(Piece::White | Piece::King, "src/images/pieces/white/K.png");
    loadTexture(Piece::White | Piece::Pawn, "src/images/pieces/white/P.png");
    loadTexture(Piece::White | Piece::Knight, "src/images/pieces/white/N.png");
    loadTexture(Piece::White | Piece::Bishop, "src/images/pieces/white/B.png");
    loadTexture(Piece::White | Piece::Rook, "src/images/pieces/white/R.png");
    loadTexture(Piece::White | Piece::Queen, "src/images/pieces/white/Q.png");

    loadTexture(Piece::Black | Piece::King, "src/images/pieces/black/k.png");
    loadTexture(Piece::Black | Piece::Pawn, "src/images/pieces/black/p.png");
    loadTexture(Piece::Black | Piece::Knight, "src/images/pieces/black/n.png");
    loadTexture(Piece::Black | Piece::Bishop, "src/images/pieces/black/b.png");
    loadTexture(Piece::Black | Piece::Rook, "src/images/pieces/black/r.png");
    loadTexture(Piece::Black | Piece::Queen, "src/images/pieces/black/q.png");
}
