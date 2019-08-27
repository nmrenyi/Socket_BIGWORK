#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <string>


class Board
{
public:
    Board();
    void setPiece(std::string, bool, int, int);
    bool askPiece(int, int);
    Piece askForPiece(int, int);
private:
    Piece status[9][9];
    bool withPiece[9][9];
};

#endif // BOARD_H
