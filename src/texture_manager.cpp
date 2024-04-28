#include "texture_manager.h"

#include <iostream>

std::map<int, sf::Texture> TextureManager::textures;

bool TextureManager::loadTexture(const int &piece, const std::string& filePath) {
    sf::Texture texture;

    if (!texture.loadFromFile(filePath)) {
        return false;
    }

    textures[piece] = texture;
    return true;
}

sf::Texture& TextureManager::getTexture(const int &piece) {
    return textures.at(piece);
}
