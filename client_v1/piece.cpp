#include "piece.h"

Piece::Piece()
{
    pawnFirstStep = true;
}

Piece::Piece(bool w, std::string s) : white(w), name(s) {}
