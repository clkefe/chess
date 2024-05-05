#ifndef PIECE_H
#define PIECE_H
#include <map>
#include <iostream>
#include <vector>

#include "board.h"

static constexpr int PIECE_TYPE_MASK        = 0b00111;
static constexpr int PIECE_WHITE_COLOR_MASK = 0b01000;
static constexpr int PIECE_BLACK_COLOR_MASK = 0b10000;
static constexpr int PIECE_COLOR_MASK = PIECE_WHITE_COLOR_MASK | PIECE_BLACK_COLOR_MASK;

// Game Constants
static constexpr int WHITE_PAWN_STARTING_RANK{6};
static constexpr int BLACK_PAWN_STARTING_RANK{1};

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

    static std::vector<int> legalMoves;

    static void loadPieceTextures();
    static bool isColor(const int &piece, const int &color);
    static int getColor(const int &piece);
    static int getType(const int &piece);

    static void generateMoves(int piece, const int& squareIndex, const int board[]);
    static void generatePawnMoves(int piece, int rank, int file, const int board[]);
    static void generateRookMoves(int piece, int rank, int file, const int board[]);
    static void generateBishopMoves(int piece, int rank, int file, const int board[]);

    static void generateLinearSlidingMoves(int piece, int rank, int file, bool isVertical, const int board[]);
    static void generateDiagonalSlidingMoves(int piece, int rank, int file, const int board[]);
};

#endif //PIECE_H
