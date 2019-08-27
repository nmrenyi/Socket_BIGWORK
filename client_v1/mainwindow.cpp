#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <sstream>
#include <string>
#include "piece.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileRead(false)
{
    ui->setupUi(this);

    black_bishop.load("/Pic/black_bishop.png");
    black_king.load(":/Pic/black_king.png");
    black_pawn.load(":/Pic/black_pawn.png");
    black_rook.load(":/Pic/black_rook.png");
    black_queen.load(":/Pic/black_queen.png");
    black_knight.load(":/Pic/black_knight.png");
    white_bishop.load("/Pic/white_bishop.png");
    white_king.load(":/Pic/white_king.png");
    white_pawn.load(":/Pic/white_pawn.png");
    white_rook.load(":/Pic/white_rook.png");
    white_queen.load(":/Pic/white_queen.png");
    white_knight.load(":/Pic/white_knight.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::pair<int, int> trans(std::pair<int, int> src) {
    int x = 8 - src.second;
    int y = src.first - 1;
    return std::make_pair(x, y);
}

void MainWindow::paintEvent(QPaintEvent * e) {
//    qDebug() << "call you paint";
    const int row = 8;
    const int line = 8;

    // 画棋盘
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    QColor whiteBlock(248,246,231);
    QColor brownBlock(195,176,145);
    QBrush whiteBrush(whiteBlock, Qt::SolidPattern);
    QBrush blackBrush(brownBlock, Qt::SolidPattern);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < line; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    painter.setBrush(whiteBrush);
                } else {
                    painter.setBrush(blackBrush);
                }
                painter.drawRect(startx + j * interval, starty + i * interval, interval, interval);
            } else {
                if (j % 2 == 1) {
                    painter.setBrush(whiteBrush);
                } else {
                    painter.setBrush(blackBrush);
                }
                painter.drawRect(startx + j * interval, starty + i * interval, interval, interval);
            }
        }
    }
//    qDebug() << "board drawed";


    if (fileRead) {
//        qDebug() << "file read";
        for (int letter = 1; letter <= row; letter++) {
            for (int number = 1; number <= line; number++) {
                if (board.askPiece(letter, number)) {
                    std::pair<int, int> now = trans(std::make_pair(letter, number));
                    int x = now.first;
                    int y = now.second;
                    Piece piece = board.askForPiece(letter, number);
//                    QPixmap tmp;
//                    tmp.load((":/Pic/black_bishop.png"));
//                    painter.drawPixmap(startx, starty, interval, interval, tmp);
//                    QBrush nowBrush(Qt::black, Qt::SolidPattern);
//                    painter.setBrush(nowBrush);
//                    painter.setBackground(Qt::OpaqueMode);
                    if (piece.white) {
                        if (piece.name == "bishop")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, white_bishop);
                        else if (piece.name == "king")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, white_king);
                        else if (piece.name == "knight")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, white_knight);
                        else if (piece.name == "queen")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, white_queen);
                        else if (piece.name == "pawn")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, white_pawn);
                        else if (piece.name == "rook")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, white_rook);
                        else
                            qDebug() << "invalid piece name";
                    } else {
                        if (piece.name == "bishop")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, black_bishop);
                        else if (piece.name == "king")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, black_king);
                        else if (piece.name == "knight")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, black_knight);
                        else if (piece.name == "queen")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, black_queen);
                        else if (piece.name == "pawn")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, black_pawn);
                        else if (piece.name == "rook")
                            painter.drawPixmap(startx + interval * y, starty + interval * x, interval, interval, black_rook);
                        else
                            qDebug() << "invalid piece name";
                    }
                }
            }
        }
    }


}

void MainWindow::on_actionReadFile_triggered()
{
//    QString fileName = QFileDialog::getOpenFileName(NULL,"标题",".","*.txt");
    QFile file(":/sample_input.txt");
//    QFile file(fileName);
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        bool white = true;
        while(!in.atEnd()) {
            QString s = in.readLine();
            if (s == "black")
                white = false;
            else if (s == "white")
                white = true;
            else {
//                qDebug() << s;
                std::string line = s.toStdString();
                std::stringstream ss;
                std::string name;
                std::string num;
                ss << line;
                ss >> name;
                ss >> num;
                int number = std::stoi(num);
                for (int i = 0; i < number; i++) {
                    std::string tmp;
                    ss >> tmp;
//                    qDebug() << int(tmp[0] - 65) << " " << int(tmp[1]);
                    board.setPiece(name, white, int(tmp[0] - 96), int(tmp[1] - 48));
                }
            }
        }
        fileRead = true;
        this->update();
    } else {
            qDebug()<<"file open failed";
    }
}
