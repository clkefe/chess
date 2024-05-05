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

int Piece::getColor(const int &piece) {
    return (piece & PIECE_COLOR_MASK);
}

int Piece::getType(const int &piece) {
    return piece & PIECE_TYPE_MASK;
}

void Piece::generateMoves(int piece, const int &squareIndex, const int board[]) {
    legalMoves.clear();

    const int rank = squareIndex / 8;
    const int file = squareIndex % 8;

    switch (getType(piece)) {
        case Pawn:
            generatePawnMoves(piece, rank, file, board);
            break;
        case Rook:
            generateRookMoves(piece, rank, file, board);
            break;
        case Bishop:
            generateBishopMoves(piece, rank, file, board);
            break;
        case Knight:
            generateKnightMoves(piece, rank, file, board);
            break;
        case Queen:
            generateQueenMoves(piece, rank, file, board);
        default:
            break;
    }
}

void Piece::generatePawnMoves(const int piece, const int rank, const int file, const int board[]) {
    // Moves upward (white pieces) --> -1
    // Moves downward (black pieces) --> 1
    const int moveDirection = isColor(piece, White) ? -1 : 1;

    // Pawns can move 2 ranks above/below if they haven't moved yet.
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

    if (file > 0 && board[leftCapture] != None && !isColor(board[leftCapture], getColor(piece))) {
        legalMoves.push_back(leftCapture);
    }

    if (file < 7 && board[rightCapture] != None && !isColor(board[rightCapture], getColor(piece))) {
        legalMoves.push_back(rightCapture);
    }

    // TODO: Check for en passant
}

void Piece::generateRookMoves(const int piece, const int rank, const int file, const int board[]) {
    generateLinearSlidingMoves(piece, rank, file, true, board);
    generateLinearSlidingMoves(piece, rank, file, false, board);
}

void Piece::generateBishopMoves(const int piece, const int rank, const int file, const int board[]) {
    generateDiagonalSlidingMoves(piece, rank, file, board);
}

void Piece::generateKnightMoves(int piece, int rank, int file, const int board[]) {
    for(int direction = 0; direction < 2; direction++) {
        const int rankMulConstant = direction == 0 ? 2 : 1;
        const int fileMulConstant = direction == 0 ? 1 : 2;

        for(int rankMultiplier = -rankMulConstant; rankMultiplier <= rankMulConstant; rankMultiplier += rankMulConstant * 2) {
            for(int fileMultiplier = -fileMulConstant; fileMultiplier <= fileMulConstant; fileMultiplier += fileMulConstant * 2) {
                const int newFile = file + fileMultiplier;
                const int newRank = rank + rankMultiplier;

                if(newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7) {
                    continue;
                }

                const int targetSquareIndex = newRank * 8 + newFile;
                const int pieceOnTargetSquare = board[targetSquareIndex];

                if(pieceOnTargetSquare == None) {
                    legalMoves.push_back(targetSquareIndex);
                } else {
                    if(!isColor(pieceOnTargetSquare, getColor(piece))) {
                        legalMoves.push_back(targetSquareIndex);
                    }
                }
            }
        }
    }
}

void Piece::generateQueenMoves(int piece, int rank, int file, const int board[]) {
    generateLinearSlidingMoves(piece, rank, file, true, board);
    generateLinearSlidingMoves(piece, rank, file, false, board);
    generateDiagonalSlidingMoves(piece, rank, file, board);
}

void Piece::generateLinearSlidingMoves(const int piece, const int rank, const int file, const bool isVertical, const int board[]) {
    for(int i = -1; i <= 1; i += 2) {
        const int startIndex = isVertical ? rank : file;
        const int endIndex = i > 0 ? 8 : -1;

        for(int k = startIndex; k != endIndex; k += i) {
            int targetSquareIndex;

            if(isVertical) {
                targetSquareIndex = k * 8 + file;
            } else {
                targetSquareIndex = rank * 8 + k;
            }

            const int pieceOnTargetSquare = board[targetSquareIndex];

            if(rank * 8 + file == targetSquareIndex) {
                continue;
            }

            if(pieceOnTargetSquare == None) {
                legalMoves.push_back(targetSquareIndex);
            } else {
                if(!isColor(pieceOnTargetSquare, getColor(piece))) {
                    legalMoves.push_back(targetSquareIndex);
                }

                break;
            }
        }
    }
}

void Piece::generateDiagonalSlidingMoves(const int piece, const int rank, const int file, const int board[]) {
    int newFile = {file};
    int newRank = {rank};

    for(int rankMultiplier = -1; rankMultiplier <= 1; rankMultiplier += 2) {
        for(int fileMultiplier = -1; fileMultiplier <= 1; fileMultiplier += 2) {
            while(true) {
                newFile = newFile + fileMultiplier;
                newRank = newRank - rankMultiplier;

                if(newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7) {
                    break;
                }

                const int targetSquareIndex = newRank * 8 + newFile;
                const int pieceOnTargetSquare = board[targetSquareIndex];

                if(pieceOnTargetSquare == None) {
                    legalMoves.push_back(targetSquareIndex);
                } else {
                    if(!isColor(pieceOnTargetSquare, getColor(piece))) {
                        legalMoves.push_back(targetSquareIndex);
                    }

                    break;
                }
            }

            newFile = {file};
            newRank = {rank};
        }
    }
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
