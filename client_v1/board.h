#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <string>
#include <iostream>


class Board
{
public:
    Board();
    void setPiece(std::string, bool, int, int);
    bool askPiece(int, int);
    Piece askForPiece(int, int);
    bool holding;

    std::pair<int, int>nowSelect;
    bool okToMove[10][10];
    void setOkToMove(int, int);
    void initOkToMove();
    Piece status[10][10];
    bool withPiece[10][10];
    bool readyForPromotion(bool ,int , int);
    void initWithPiece();
private:
    bool checkInBoard(int, int);
    bool checkAlly(Piece, Piece);
};

#endif // BOARD_H
