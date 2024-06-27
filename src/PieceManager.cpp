#include "PieceManager.h"

const std::map<char, int> PieceManager::pieceCharToValue = {
    {'K', White | King},
    {'P', White | Pawn},
    {'N', White | Knight},
    {'B', White | Bishop},
    {'R', White | Rook},
    {'Q', White | Queen},

    {'k', Black | King},
    {'p', Black | Pawn},
    {'n', Black | Knight},
    {'b', Black | Bishop},
    {'r', Black | Rook},
    {'q', Black | Queen},
};

bool PieceManager::isColor(const Piece &piece, const int &color) {
    return (piece.getColor() & PIECE_COLOR_MASK) == color;
}

void PieceManager::generateMoves() {
    // switch (getType()) {
    //     case Pawn:
    //         generatePawnMoves();
    //         break;
    //     case Rook:
    //         generateRookMoves(piece);
    //         break;
    //     case Bishop:
    //         generateBishopMoves(piece);
    //         break;
    //     case Knight:
    //         generateKnightMoves(piece);
    //         break;
    //     case Queen:
    //         generateQueenMoves(piece);
    //         break;
    //     case King:
    //         generateKingMoves(piece);
    //         break;
    //     default:
    //         break;
    // }
}

// void PieceManager::generatePawnMoves(const Piece &piece) {
//     // Moves upward (white pieces) --> -1
//     // Moves downward (black pieces) --> 1
//     const int moveDirection = this->isColor(White) ? -1 : 1;
//
//     // Pawns can move 2 ranks above/below if they haven't moved yet.
//     const bool isPawnOnStartingRank = m_rank == WHITE_PAWN_STARTING_RANK || m_rank == BLACK_PAWN_STARTING_RANK;
//     const int numberOfForwardMoves = isPawnOnStartingRank ? 2 : 1;
//
//     // Forward Pawn Moves
//     for (int i = 1; i <= numberOfForwardMoves; i++) {
//         const int targetSquareIndex = (m_rank + (i * moveDirection)) * 8 + m_file;
//
//         if (m_board.square[targetSquareIndex] != None) {
//             break;
//         }
//
//         legalMoves.push_back(targetSquareIndex);
//     }
//
//     // Capturing moves to the left and right
//     const int leftCapture = (m_rank + moveDirection) * 8 + m_file - 1;
//     const int rightCapture = (m_rank + moveDirection) * 8 + m_file + 1;
//
//     if (m_file > 0 && m_board.square[leftCapture] != None && !isColor(m_board.square[leftCapture], getColor())) {
//         legalMoves.push_back(leftCapture);
//     }
//
//     if (m_file < 7 && m_board.square[rightCapture] != None && !isColor(m_board.square[rightCapture], getColor())) {
//         legalMoves.push_back(rightCapture);
//     }
//
//     // TODO: Check for en passant
// }
//
// void PieceManager::generateRookMoves(const Piece &piece) {
//     generateLinearSlidingMoves(piece, rank, file, true, board);
//     generateLinearSlidingMoves(piece, rank, file, false, board);
// }
//
// void PieceManager::generateBishopMoves(const Piece &piece) {
//     generateDiagonalSlidingMoves(piece, rank, file, board);
// }
//
// void PieceManager::generateKnightMoves(const Piece &piece) {
//     for (int direction = 0; direction < 2; direction++) {
//         const int rankMulConstant = direction == 0 ? 2 : 1;
//         const int fileMulConstant = direction == 0 ? 1 : 2;
//
//         for (int rankMultiplier = -rankMulConstant; rankMultiplier <= rankMulConstant;
//              rankMultiplier += rankMulConstant * 2) {
//             for (int fileMultiplier = -fileMulConstant; fileMultiplier <= fileMulConstant;
//                  fileMultiplier += fileMulConstant * 2) {
//                 const int newFile = file + fileMultiplier;
//                 const int newRank = rank + rankMultiplier;
//
//                 if (newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7) {
//                     continue;
//                 }
//
//                 const int targetSquareIndex = newRank * 8 + newFile;
//                 const int pieceOnTargetSquare = board[targetSquareIndex];
//
//                 if (pieceOnTargetSquare == None) {
//                     legalMoves.push_back(targetSquareIndex);
//                 } else {
//                     if (!isColor(pieceOnTargetSquare, getColor(piece))) {
//                         legalMoves.push_back(targetSquareIndex);
//                     }
//                 }
//             }
//         }
//     }
// }
//
// void PieceManager::generateQueenMoves(const Piece &piece) {
//     generateLinearSlidingMoves(piece, rank, file, true, board);
//     generateLinearSlidingMoves(piece, rank, file, false, board);
//     generateDiagonalSlidingMoves(piece, rank, file, board);
// }
//
// void PieceManager::generateKingMoves(const Piece &piece) {
//     for (int i = -1; i <= 1; i++) {
//         for (int j = -1; j <= 1; j++) {
//             const int newFile = file + i;
//             const int newRank = rank + j;
//
//             if (newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7) {
//                 continue;
//             }
//
//             const int targetSquareIndex = newRank * 8 + newFile;
//             const int pieceOnTargetSquare = board[targetSquareIndex];
//
//             if (isColor(pieceOnTargetSquare, getColor(piece))) {
//                 continue;
//             }
//
//             legalMoves.push_back(targetSquareIndex);
//         }
//     }
// }
//
// void PieceManager::generateLinearSlidingMoves(const Piece &piece, const bool isVertical) {
//     for (int i = -1; i <= 1; i += 2) {
//         const int startIndex = isVertical ? rank : file;
//         const int endIndex = i > 0 ? 8 : -1;
//
//         for (int k = startIndex; k != endIndex; k += i) {
//             int targetSquareIndex;
//
//             if (isVertical) {
//                 targetSquareIndex = k * 8 + file;
//             } else {
//                 targetSquareIndex = rank * 8 + k;
//             }
//
//             const int pieceOnTargetSquare = board[targetSquareIndex];
//
//             if (rank * 8 + file == targetSquareIndex) {
//                 continue;
//             }
//
//             if (pieceOnTargetSquare == None) {
//                 legalMoves.push_back(targetSquareIndex);
//             } else {
//                 if (!isColor(pieceOnTargetSquare, getColor(piece))) {
//                     legalMoves.push_back(targetSquareIndex);
//                 }
//
//                 break;
//             }
//         }
//     }
// }
//
// void PieceManager::generateDiagonalSlidingMoves(const Piece &piece) {
//     int newFile = {file};
//     int newRank = {rank};
//
//     for (int rankMultiplier = -1; rankMultiplier <= 1; rankMultiplier += 2) {
//         for (int fileMultiplier = -1; fileMultiplier <= 1; fileMultiplier += 2) {
//             while (true) {
//                 newFile = newFile + fileMultiplier;
//                 newRank = newRank - rankMultiplier;
//
//                 if (newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7) {
//                     break;
//                 }
//
//                 const int targetSquareIndex = newRank * 8 + newFile;
//                 const int pieceOnTargetSquare = board[targetSquareIndex];
//
//                 if (pieceOnTargetSquare == None) {
//                     legalMoves.push_back(targetSquareIndex);
//                 } else {
//                     if (!isColor(pieceOnTargetSquare, getColor(piece))) {
//                         legalMoves.push_back(targetSquareIndex);
//                     }
//
//                     break;
//                 }
//             }
//
//             newFile = {file};
//             newRank = {rank};
//         }
//     }
// }
