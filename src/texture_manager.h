#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {
public:
    static std::map<int, sf::Texture> textures;

    static bool loadTexture(const int &piece, const std::string &filePath);

    static sf::Texture &getTexture(const int &piece);

    static void loadPieceTextures();
};

#endif // TEXTURE_MANAGER_H
