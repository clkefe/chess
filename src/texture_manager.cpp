#include "texture_manager.h"

#include <iostream>
#include "PieceManager.h"

std::map<int, sf::Texture> TextureManager::textures;

bool TextureManager::loadTexture(const int &piece, const std::string &filePath) {
    sf::Texture texture;

    if (!texture.loadFromFile(filePath)) {
        return false;
    }

    textures[piece] = texture;
    return true;
}

sf::Texture &TextureManager::getTexture(const int piece) {
    return textures.at(piece);
}

void TextureManager::loadPieceTextures() {
    loadTexture(PieceManager::White | PieceManager::King, "src/images/pieces/white/K.png");
    loadTexture(PieceManager::White | PieceManager::Pawn, "src/images/pieces/white/P.png");
    loadTexture(PieceManager::White | PieceManager::Knight, "src/images/pieces/white/N.png");
    loadTexture(PieceManager::White | PieceManager::Bishop, "src/images/pieces/white/B.png");
    loadTexture(PieceManager::White | PieceManager::Rook, "src/images/pieces/white/R.png");
    loadTexture(PieceManager::White | PieceManager::Queen, "src/images/pieces/white/Q.png");

    loadTexture(PieceManager::Black | PieceManager::King, "src/images/pieces/black/k.png");
    loadTexture(PieceManager::Black | PieceManager::Pawn, "src/images/pieces/black/p.png");
    loadTexture(PieceManager::Black | PieceManager::Knight, "src/images/pieces/black/n.png");
    loadTexture(PieceManager::Black | PieceManager::Bishop, "src/images/pieces/black/b.png");
    loadTexture(PieceManager::Black | PieceManager::Rook, "src/images/pieces/black/r.png");
    loadTexture(PieceManager::Black | PieceManager::Queen, "src/images/pieces/black/q.png");
}
