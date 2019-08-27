#ifndef PIECE_H
#define PIECE_H
#include <string>


class Piece
{
public:
    Piece();
    Piece(bool, std::string);
    bool white;
    std::string name;
    bool pawnFirstStep;
};

#endif // PIECE_H
