#include "board.h"
#include <QDebug>

Board::Board()
{
    holding = false;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            withPiece[i][j] = false;
            okToMove[i][j] = false;
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
bool Board::checkInBoard(int k, int l) {
    if (k >= 1 && k <= 8 && l >= 1 && l <= 8)
        return true;
    return false;
}

void Board::initOkToMove() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++)
            okToMove[i][j] = false;
    }
}
bool Board::readyForPromotion(bool white, int letter, int number) {
    int edge = -1;
    if (white)
        edge = 8;
    else
        edge = 1;
    if (number == edge)
        return true;
    return false;

}
void Board::setOkToMove(int letter, int number) {
    Piece now = status[letter][number];
    // 兵升变
    if (now.name == "pawn") {
        int ONE, TWO;
        if (now.white) {
            ONE = 1;
            TWO = 2;
        } else {
            ONE = -1;
            TWO = -2;
        }
//        qDebug() << "it is pawn";
        if (now.pawnFirstStep) {
//            qDebug() << "its first step";
            if (checkInBoard(letter, number + ONE) && withPiece[letter][number + ONE]) {
//                qDebug() << "none ok";
            } else if (checkInBoard(letter, number + TWO) && withPiece[letter][number + TWO]) {
                qDebug() << QString::fromStdString(askForPiece(letter, number + TWO).name);
//                qDebug() << "ONE ok";
                okToMove[letter][number + ONE] = true;
            } else {
//                qDebug() << "TWO ok" << letter << number + ONE;
                if (checkInBoard(letter, number + ONE))
                    okToMove[letter][number + ONE] = true;
                if (checkInBoard(letter, number + TWO))
                    okToMove[letter][number + TWO] = true;
            }
        } else {
            if (checkInBoard(letter, number + ONE) && !withPiece[letter][number + ONE]) {
                okToMove[letter][number + ONE] = true;
            }
        }

//        qDebug()  << "ok zuoshang" << checkInBoard(letter - ONE, number + ONE) << withPiece[letter - ONE][number + ONE];
//        qDebug() << "ok youshang" << checkInBoard(letter + ONE, number + ONE) << withPiece[letter + ONE][number + ONE];
        if (!checkAlly(status[letter][number], status[letter + ONE][number + ONE]) && checkInBoard(letter + ONE, number + ONE) && withPiece[letter + ONE][number + ONE])
            okToMove[letter + ONE][number + ONE] = true;
        if (!checkAlly(status[letter][number], status[letter - ONE][number + ONE]) && checkInBoard(letter - ONE, number + ONE) && withPiece[letter - ONE][number + ONE])
            okToMove[letter - ONE][number + ONE] = true;
    }
    else if (now.name == "rook") {
        for (int i = letter + 1; checkInBoard(i, number); i++) {
            if (!withPiece[i][number])
                okToMove[i][number] = true;
            else {
                if (!checkAlly(status[letter][number], status[i][number])) {
                    okToMove[i][number] = true;
                }
                break;
            }
        }
        for (int i = letter - 1; checkInBoard(i, number); i--) {
            if (!withPiece[i][number])
                okToMove[i][number] = true;
            else {
                if (!checkAlly(status[letter][number], status[i][number])) {
                    okToMove[i][number] = true;
                }
                break;
            }
        }
        for (int i = number + 1; checkInBoard(letter, i); i++) {
            if (!withPiece[letter][i])
                okToMove[letter][i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter][i]))
                    okToMove[letter][i] = true;
                break;
            }
        }
        for (int i = number - 1; checkInBoard(letter, i); i--) {
            if (!withPiece[letter][i])
                okToMove[letter][i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter][i]))
                    okToMove[letter][i] = true;
                break;
            }
        }

    } else if (now.name == "bishop") {
        for (int i = 1; checkInBoard(letter + i, number + i); i++) {
            if (!withPiece[letter + i][number + i])
                okToMove[letter + i][number + i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number + i]))
                    okToMove[letter + i][number + i] = true;
                break;
            }
        }
        for (int i = -1; checkInBoard(letter + i, number + i); i--) {
            if (!withPiece[letter + i][number + i])
                okToMove[letter + i][number + i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number + i]))
                    okToMove[letter + i][number + i] = true;
                break;
            }
        }
        for (int i = 1; checkInBoard(letter + i, number - i); i++) {
            if (!withPiece[letter + i][number - i])
                okToMove[letter + i][number - i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number - i]))
                    okToMove[letter + i][number - i] = true;
                break;
            }
        }
        for (int i = -1; checkInBoard(letter + i, number - i); i--) {
            if (!withPiece[letter + i][number - i])
                okToMove[letter + i][number - i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number - i]))
                    okToMove[letter + i][number - i] = true;
                break;
            }
        }
    } else if (now.name == "queen") {
        for (int i = 1; checkInBoard(letter + i, number + i); i++) {
            if (!withPiece[letter + i][number + i])
                okToMove[letter + i][number + i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number + i]))
                    okToMove[letter + i][number + i] = true;
                break;
            }
        }
        for (int i = -1; checkInBoard(letter + i, number + i); i--) {
            if (!withPiece[letter + i][number + i])
                okToMove[letter + i][number + i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number + i]))
                    okToMove[letter + i][number + i] = true;
                break;
            }
        }
        for (int i = 1; checkInBoard(letter + i, number - i); i++) {
            if (!withPiece[letter + i][number - i])
                okToMove[letter + i][number - i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number - i]))
                    okToMove[letter + i][number - i] = true;
                break;
            }
        }
        for (int i = -1; checkInBoard(letter + i, number - i); i--) {
            if (!withPiece[letter + i][number - i])
                okToMove[letter + i][number - i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter + i][number - i]))
                    okToMove[letter + i][number - i] = true;
                break;
            }
        }
        for (int i = letter + 1; checkInBoard(i, number); i++) {
            if (!withPiece[i][number])
                okToMove[i][number] = true;
            else {
                if (!checkAlly(status[letter][number], status[i][number])) {
                    okToMove[i][number] = true;
                }
                break;
            }
        }
        for (int i = letter - 1; checkInBoard(i, number); i--) {
            if (!withPiece[i][number])
                okToMove[i][number] = true;
            else {
                if (!checkAlly(status[letter][number], status[i][number])) {
                    okToMove[i][number] = true;
                }
                break;
            }
        }
        for (int i = number + 1; checkInBoard(letter, i); i++) {
            if (!withPiece[letter][i])
                okToMove[letter][i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter][i]))
                    okToMove[letter][i] = true;
                break;
            }
        }
        for (int i = number - 1; checkInBoard(letter, i); i--) {
            if (!withPiece[letter][i])
                okToMove[letter][i] = true;
            else {
                if (!checkAlly(status[letter][number], status[letter][i]))
                    okToMove[letter][i] = true;
                break;
            }
        }
    } else if (now.name == "king") {
        if (checkInBoard(letter, number + 1)) {
            if (!withPiece[letter][number + 1])
                okToMove[letter][number + 1] = true;
            else {
                if (!checkAlly(status[letter][number + 1],status[letter][number]))
                    okToMove[letter][number + 1] = true;
            }
        }
        if (checkInBoard(letter, number - 1)) {
            if (!withPiece[letter][number - 1])
                okToMove[letter][number - 1] = true;
            else {
                if (!checkAlly(status[letter][number - 1],status[letter][number]))
                    okToMove[letter][number - 1] = true;
            }
        }
        if (checkInBoard(letter + 1, number + 1)) {
            if (!withPiece[letter + 1][number + 1])
                okToMove[letter + 1][number + 1] = true;
            else {
                if (!checkAlly(status[letter + 1][number + 1],status[letter][number]))
                    okToMove[letter + 1][number + 1] = true;
            }
        }
        if (checkInBoard(letter + 1, number - 1)) {
            if (!withPiece[letter + 1][number - 1])
                okToMove[letter + 1][number - 1] = true;
            else {
                if (!checkAlly(status[letter + 1][number - 1],status[letter][number]))
                    okToMove[letter + 1][number - 1] = true;
            }
        }


        if (checkInBoard(letter - 1, number + 1)) {
            if (!withPiece[letter - 1][number + 1])
                okToMove[letter - 1][number + 1] = true;
            else {
                if (!checkAlly(status[letter - 1][number + 1],status[letter][number]))
                    okToMove[letter - 1][number + 1] = true;
            }
        }
        if (checkInBoard(letter - 1, number - 1)) {
            if (!withPiece[letter - 1][number - 1])
                okToMove[letter - 1][number - 1] = true;
            else {
                if (!checkAlly(status[letter - 1][number - 1],status[letter][number]))
                    okToMove[letter - 1][number - 1] = true;
            }
        }




        if (checkInBoard(letter + 1, number)) {
            if (!withPiece[letter + 1][number])
                okToMove[letter + 1][number] = true;
            else {
                if (!checkAlly(status[letter + 1][number],status[letter][number]))
                    okToMove[letter + 1][number] = true;
            }
        }
        if (checkInBoard(letter - 1, number)) {
            if (!withPiece[letter - 1][number])
                okToMove[letter - 1][number] = true;
            else {
                if (!checkAlly(status[letter - 1][number],status[letter][number]))
                    okToMove[letter - 1][number] = true;
            }
        }
    } else if (now.name == "knight") {
        if (checkInBoard(letter - 2, number + 1)) {
            if (!withPiece[letter - 2][number + 1])
                okToMove[letter - 2][number + 1] = true;
            else {
                if (!checkAlly(status[letter - 2][number + 1],status[letter][number]))
                    okToMove[letter - 2][number + 1] = true;
            }
        }
        if (checkInBoard(letter + 2, number + 1)) {
            if (!withPiece[letter + 2][number + 1])
                okToMove[letter + 2][number + 1] = true;
            else {
                if (!checkAlly(status[letter + 2][number + 1],status[letter][number]))
                    okToMove[letter + 2][number + 1] = true;
            }
        }
        if (checkInBoard(letter - 2, number - 1)) {
            if (!withPiece[letter - 2][number - 1])
                okToMove[letter - 2][number - 1] = true;
            else {
                if (!checkAlly(status[letter - 2][number - 1],status[letter][number]))
                    okToMove[letter - 2][number - 1] = true;
            }
        }
        if (checkInBoard(letter + 2, number - 1)) {
            if (!withPiece[letter + 2][number - 1])
                okToMove[letter + 2][number - 1] = true;
            else {
                if (!checkAlly(status[letter + 2][number - 1],status[letter][number]))
                    okToMove[letter + 2][number - 1] = true;
            }
        }

        if (checkInBoard(letter + 1, number + 2)) {
            if (!withPiece[letter + 1][number + 2])
                okToMove[letter + 1][number + 2] = true;
            else {
                if (!checkAlly(status[letter + 1][number + 2], status[letter][number]))
                    okToMove[letter + 1][number + 2] = true;
            }
        }
        if (checkInBoard(letter + 1, number - 2)) {
            if (!withPiece[letter + 1][number - 2])
                okToMove[letter + 1][number - 2] = true;
            else {
                if (!checkAlly(status[letter + 1][number - 2], status[letter][number]))
                    okToMove[letter + 1][number - 2] = true;
            }
        }
        if (checkInBoard(letter - 1, number + 2)) {
            if (!withPiece[letter - 1][number + 2])
                okToMove[letter - 1][number + 2] = true;
            else {
                if (!checkAlly(status[letter - 1][number + 2], status[letter][number]))
                    okToMove[letter - 1][number + 2] = true;
            }
        }
        if (checkInBoard(letter - 1, number - 2)) {
            if (!withPiece[letter - 1][number - 2])
                okToMove[letter - 1][number - 2] = true;
            else {
                if (!checkAlly(status[letter - 1][number - 2], status[letter][number]))
                    okToMove[letter - 1][number - 2] = true;
            }
        }
    }
}

bool Board::checkAlly(Piece p1, Piece p2) {
    if (p1.white == p2.white)
        return true;
    return false;
}
