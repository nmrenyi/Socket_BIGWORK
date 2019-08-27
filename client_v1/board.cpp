#include "board.h"

Board::Board()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            withPiece[i][j] = false;
        }
    }
}

void Board::setPiece(std::string name, bool white, int letter, int number) {
    status[letter][number].white = white;
    status[letter][number].name = name;
    withPiece[letter][number] = true;
}

bool Board::askPiece(int i, int j) {
    return withPiece[i][j];
}

Piece Board::askForPiece(int letter, int number) {
    return status[letter][number];
}
