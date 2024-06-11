#ifndef PIECE_H
#define PIECE_H
#include <vector>

class Piece {
    /**
     * This is a 5-bit int representation for the piece type and color.
     *
     * The left two bits represent the color
     *  - 8: White
     *      - 16 Black
     *
     * The right three bits represent the type
     *      - 0: None
     *      - 1: King
     *      - 2 Pawn
     *      - 3: Knight
     *      - 4: Bishop
     *      - 5: Rook
     *      - 6: Queen
     *
     *  ex.
     *      - Black Pawn: 10001
     *      - White Knight: 10011
    **/
    int m_identifier;

    std::vector<int> m_legalMoves{};

    int m_rank{0};
    int m_file{0};

public:
    explicit Piece(int identifier);
    ~Piece() = default;

    int getColor() const;
    int getType() const;

    void generateMoves();
};

#endif //PIECE_H
