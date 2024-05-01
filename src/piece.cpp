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

std::vector<int> Piece::legalMoves{};

bool Piece::isColor(const int &piece, const int &color) {
    return (piece & PIECE_COLOR_MASK)  == color;
}

bool Piece::getColor(const int &piece) {
    return (piece & PIECE_COLOR_MASK);
}

std::vector<int> Piece::generateLegalPawnMoves(int piece, const int &squareIndex, const int board[]) {
    legalMoves.clear();

    const int rank = squareIndex / 8;
    const int file = squareIndex % 8;

    // Moves upward (white pieces) --> -1
    // Moves downward (black pieces) --> 1
    const int moveDirection = isColor(piece, White) ? -1 : 1;

    const bool isPawnOnStartingRank = rank == WHITE_PAWN_STARTING_RANK || rank == BLACK_PAWN_STARTING_RANK;
    const int numberOfForwardMoves = isPawnOnStartingRank ? 2 : 1;


    // Forward Pawn Moves
    for(int i = 1; i <= numberOfForwardMoves; i++) {
        const int targetSquareIndex = (rank + (i * moveDirection) ) * 8 + file;

        if(board[targetSquareIndex] != None) {
            break;
        }

        legalMoves.push_back(targetSquareIndex);
    }

    // Capturing moves to the left and right
    const int leftCapture = (rank + moveDirection) * 8 + file - 1;
    const int rightCapture = (rank + moveDirection) * 8 + file + 1;

    if (file > 0 && board[leftCapture] != None && !isColor(board[leftCapture], piece & PIECE_COLOR_MASK)) {
        legalMoves.push_back(leftCapture);
    }
    if (file < 7 && board[rightCapture] != None && !isColor(board[rightCapture], piece & PIECE_COLOR_MASK)) {
        legalMoves.push_back(rightCapture);
    }

    // TODO: Check for en passant

    return legalMoves;
}


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
