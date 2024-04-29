#ifndef PIECE_H
#define PIECE_H
#include <map>

constexpr int PIECE_TYPE_MASK = 0b00111;
static constexpr int PIECE_WHITE_COLOR_MASK = 0b01000;
static constexpr int PIECE_BLACK_COLOR_MASK = 0b10000;
static constexpr int PIECE_COLOR_MASK = PIECE_WHITE_COLOR_MASK & PIECE_BLACK_COLOR_MASK;

class Piece {
public:
    // PIECE TYPE
    static constexpr int None{0};
    static constexpr int King{1};
    static constexpr int Pawn{2};
    static constexpr int Knight{3};
    static constexpr int Bishop{4};
    static constexpr int Rook{5};
    static constexpr int Queen{6};

    // PIECE COLOR
    static constexpr int White{8};
    static constexpr int Black{16};

    static const std::map<char, int> pieceCharToValue;

    static void loadPieceTextures();
    static bool isColor(const int &piece, const int &color);
};

#endif //PIECE_H
