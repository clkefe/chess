#include "board.h"

#include "piece.h"
#include "texture_manager.h"

Board::Board(sf::RenderWindow& window) : m_window{window}, board{}, selectedPieceIndex{-1}, colorToMove{} {
    loadFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::drawBackground() {
    // We use 256 vertex because each quad needs 4 vertex, and there are 64 squares on a chess board (64*4=256).
    sf::VertexArray background(sf::Quads, 256);

    float pos_x{0};
    float pos_y{0};

    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            const int startingIndex = (rank * 8 + file) * 4; // Muliply by 4 because each quad has 4 vertex.

            background[startingIndex].position     = sf::Vector2f(pos_x,       pos_y + 100); // left-bottom
            background[startingIndex + 1].position = sf::Vector2f(pos_x,       pos_y      ); // left-top
            background[startingIndex + 2].position = sf::Vector2f(pos_x + 100, pos_y      ); // right-top
            background[startingIndex + 3].position = sf::Vector2f(pos_x + 100, pos_y + 100); // right-bottom

            // Set the color of each vertex of each quad/square (each quad has 4 vertex).
            const sf::Color squareColor = (rank + file) % 2 == 0 ? COLOR_GREEN : COLOR_WHITE;
            for(int j = 0; j < 4; j++) {
                background[startingIndex + j].color = squareColor;
            }

            pos_x += 100.f;
        }

        pos_y += 100.f;
        pos_x = 0;
    }

    m_window.draw(background);
}

void Board::drawPieces() {
        for(int i = 0; i < 64; i++) {
            if(board[i] != Piece::None) {
                const int piece = board[i];

                sf::Sprite sprite;
                sprite.setTexture(TextureManager::getTexture(piece));

                const int rank = i / 8;
                const int file = i % 8;

                const float pos_x = static_cast<float>(file) * 100;
                const float pos_y = static_cast<float>(rank) * 100;

                // Skip rendering the selected piece now. It will be rendered last so it is on the top.
                if(i == selectedPieceIndex) {
                    selectedPieceSprite = sprite;
                    continue;
                }

                sprite.setPosition(pos_x, pos_y);

                m_window.draw(sprite);
            }
        }

        if(selectedPieceIndex != -1) {
            const float pos_x = static_cast<float>(sf::Mouse::getPosition(m_window).x) - 50;
            const float pos_y = static_cast<float>(sf::Mouse::getPosition(m_window).y) - 50;

            selectedPieceSprite.setPosition(pos_x, pos_y);
            m_window.draw(selectedPieceSprite);
        }
}

void Board::grabPiece() {
    const int howeredSquareIndex = getHoveredSquareIndex();
    const int selectedPiece = board[howeredSquareIndex];

    if(selectedPiece == Piece::None) {
        return;
    }

    if(!Piece::isColor(selectedPiece, colorToMove)) {
        return;
    }

    selectedPieceIndex = howeredSquareIndex;
}

void Board::releasePiece() {
    const int releasedSquareIndex = getHoveredSquareIndex();

    const int selectedPiece = board[selectedPieceIndex];

    if(selectedPieceIndex == releasedSquareIndex) {
        resetSelectedPiece();
        return;
    }

    //TODO: This should work for all types of pieces!
    const std::vector<int> legalMoves = Piece::getLegalPawnMoves(selectedPiece, selectedPieceIndex, board);

    for(int i{0}; i < legalMoves.size(); i++) {
        if(releasedSquareIndex == legalMoves.at(i)) {
            board[selectedPieceIndex] = Piece::None;
            board[releasedSquareIndex] = selectedPiece;

            colorToMove = colorToMove == Piece::White ? Piece::Black : Piece::White;
            resetSelectedPiece();
        }
    }
}

void Board::resetSelectedPiece() {
    selectedPieceIndex = -1;
    selectedPieceSprite = {};
}

int Board::getHoveredSquareIndex() const {
    const int mousePosX = sf::Mouse::getPosition(m_window).x;
    const int mousePosY = sf::Mouse::getPosition(m_window).y;

    const int mouseOnRank = mousePosY / 100;
    const int mouseOnFile = mousePosX / 100;

    return mouseOnRank * 8 + mouseOnFile;
}

void Board::loadFromFEN(const std::string &FEN) {
    const std::string piecePlacement = FEN.substr(0, FEN.find(' '));

    std::string colorToMoveString = FEN.substr(FEN.find(' ') + 1, std::size(FEN));
    colorToMoveString = colorToMoveString.substr(0, colorToMoveString.find(' '));

    colorToMove = colorToMoveString == "w" ? Piece::White : Piece::Black;

    int rank{0};
    int file{0};

    for(char c : piecePlacement) {
        if(isdigit(c)) {
            const int numberOfEmptySquares = c - '0'; // char to int conversion
            file += numberOfEmptySquares;
        } else if(c == '/') {
            rank++;
            file = 0;
        } else {
            board[rank * 8 + file] = Piece::pieceCharToValue.at(c);
            file++;
        }
    }
}