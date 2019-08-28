#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <sstream>
#include <QMouseEvent>
#include <string>
#include "piece.h"
#include <QFile>
#include <QFileDialog>
#include "dialog.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QRadioButton>
#include <QByteArray>
#include <QSignalMapper>
#include <QTime>
#include "ui_dialog.h"
#include "serverset.h"
#include "connectto.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileRead(false)
{

    ui->setupUi(this);
    black_bishop.load(":/Pic/black_bishop.png");
    black_king.load(":/Pic/black_king.png");
    black_pawn.load(":/Pic/black_pawn.png");
    black_rook.load(":/Pic/black_rook.png");
    black_queen.load(":/Pic/black_queen.png");
    black_knight.load(":/Pic/black_knight.png");
    white_bishop.load(":/Pic/white_bishop.png");
    white_king.load(":/Pic/white_king.png");
    white_pawn.load(":/Pic/white_pawn.png");
    white_rook.load(":/Pic/white_rook.png");
    white_queen.load(":/Pic/white_queen.png");
    white_knight.load(":/Pic/white_knight.png");
    nowOn = true;
    timer = new QTimer;
    oneSec = new QTimer;
    connect(oneSec, SIGNAL(timeout()), this, SLOT(minus()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUp()));
    connect(this, SIGNAL(loseSig(bool)), this, SLOT(LOSE(bool)));
    statusRead = false;
    nowTime = 60;
    ui->lcd->display(60);

}
void MainWindow::timerUp() {
    QMessageBox::information(nullptr, "time up", "time up");
    timer->stop();
    oneSec->stop();
    emit(loseSig(nowOn));
}

void MainWindow::LOSE(bool l) {
    QByteArray* arr = new QByteArray;
    arr->clear();

    if (l){
        arr->append("whitelose");
        QMessageBox::information(nullptr, "white lose, black win", "white lose, black win");
    }
    else {
        arr->append("blacklose");
        QMessageBox::information(nullptr, "black lose, white win", "black lose, white win");
    }
    readWriteSocket->write(arr->data());
}

void MainWindow::minus() {
    nowTime--;
    ui->lcd->display(nowTime);
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


//    if (fileRead) {
//        qDebug() << "file read";
        for (int letter = 1; letter <= row; letter++) {
            for (int number = 1; number <= line; number++) {
                if (board.askPiece(letter, number)) {
                    std::pair<int, int> now = trans(std::make_pair(letter, number));
                    int x = now.first;
                    int y = now.second;
                    Piece piece = board.askForPiece(letter, number);
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
//    }
    if (board.holding) {
        qDebug() << "it is holding";
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < line; j++) {
                int letter = j + 1;
                int number = 8 - i;
//                qDebug() << letter << number;
                if (board.okToMove[letter][number]) {
                    qDebug() << "drawing " << i << " " << j << " " <<startx + j * interval <<" "<< starty + i + interval;
                    QColor qc(Qt::green);
                    qc.setAlpha(60);
                    QBrush okBrush(qc, Qt::SolidPattern);
                    painter.setBrush(okBrush);
                    painter.drawRect(startx + j * interval, starty + i * interval, interval, interval);
                }
            }
        }
        QColor nowSelectColor(Qt::cyan);
        nowSelectColor.setAlpha(60);
        QBrush nowBrush(nowSelectColor, Qt::SolidPattern);
        painter.setBrush(nowBrush);
        int x = 8 - board.nowSelect.second;
        int y = board.nowSelect.first - 1;
        painter.drawRect(startx + y * interval, starty + x * interval, interval, interval);
    }
}

void MainWindow::readStatus(QString qs) {
    QTextStream in (&qs);
//        qDebug() << in.readAll();
    bool white = true;
//    bool fisrtLine = true;
    while(!in.atEnd()) {
        QString s = in.readLine();
        if (s == "black")
            white = false;
        else if (s == "white")
            white = true;
        else if (s == "true")
            nowOn = true;
        else if (s == "false")
            nowOn = false;
        else if (s == "whitelose")
            QMessageBox::information(nullptr, "black win, white lose", "black win, white lose");
        else if (s == "blacklose")
            QMessageBox::information(nullptr, "black win, white lose", "white win, black lose");
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
    if (!statusRead) {
        nowTime = 60;
        timer->start(60000);
        oneSec->start(1000);
    }
}

void MainWindow::readStatus(QFile& qs) {
    QTextStream in (&qs);
//        qDebug() << in.readAll();
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
}

void MainWindow::on_actionReadFile_triggered()
{
    nowTime = 60;
    timer->start(60000);
    oneSec->start(1000);
    board.initWithPiece();
//    QString fileName = QFileDialog::getOpenFileName(NULL,"标题",".","*.txt");
    QFile file(":/sample_input.txt");
//    QFile file(fileName);
    if (file.open(QFile::ReadOnly)) {
        readStatus(file);
        fileRead = true;
        this->update();
        sendStatus();
    } else {
            qDebug()<<"file open failed";
    }
}


void MainWindow::setIt(int i) {
    this->choice = i;
    int letter = board.nowSelect.first;
    int number = board.nowSelect.second;
    if (choice == 0) {
        board.status[letter][number].name = "queen";
        this->update();
    } else if (choice == 1) {
        Piece tmp = board.status[letter][number];
        board.status[letter][number] = Piece(tmp.white, "rook");
        this->update();
    } else if (choice == 2) {
        Piece tmp = board.status[letter][number];
        board.status[letter][number] = Piece(tmp.white, "bishop");
        this->update();
    } else if (choice == 3) {
        Piece tmp = board.status[letter][number];
        board.status[letter][number] = Piece(tmp.white, "knight");
        this->update();
    } else {
        qDebug() << " you haven't choose the promotion choice = " << choice;
    }
    sendStatus();
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    qDebug() << "in event choice = " << choice;
    qDebug() << "your name please" << QString::fromStdString(board.status[6][1].name);
    if (e->button() == Qt::LeftButton) {
        if (nowOn == myID)
        {
            int x = (e->y() - starty ) / interval;
            int y = (e->x() - startx ) / interval;
            int letter = y + 1;
            int number = 8 - x;
            if (board.holding) {
                if (letter == board.nowSelect.first && number == board.nowSelect.second) {
                    board.holding = false;
                    board.initOkToMove();
                    this->update();
                } else if (board.okToMove[letter][number]) {
                    board.withPiece[letter][number] = true;
                    board.withPiece[board.nowSelect.first][board.nowSelect.second] = false;
                    board.status[letter][number] = board.status[board.nowSelect.first][board.nowSelect.second];
                    board.holding = false;
                    board.nowSelect = std::make_pair(letter, number);
                    if (board.status[letter][number].name == "pawn")
                        board.status[letter][number].pawnFirstStep = false;
                    board.initOkToMove();

                    if (board.status[letter][number].name == "pawn" && board.readyForPromotion(board.status[letter][number].white, letter, number)) {
                        Dialog* dialog = new Dialog;
                        connect(dialog, SIGNAL(selected(int)), this, SLOT(setIt(int)));
                        dialog->show();
                    }
                    this->update();
                    nowOn ^= 1;
                    sendStatus();
                } else {
                    board.holding = false;
                    board.initOkToMove();
                    this->update();
                }
            } else {
                if (board.askPiece(letter, number) && board.status[letter][number].white == nowOn) {
                    board.holding = true;
                    board.nowSelect = std::make_pair(letter, number);
                    board.setOkToMove(letter, number);
                    this->update();
                }
            }
        }
    }
    bool whiteKing = false;
    bool blackKing = false;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board.status[i][j].name == "king"){
                if (board.status[i][j].white)
                    whiteKing = true;
                else {
                    blackKing = true;
                }
            }
        }
    }
    if (!blackKing) {
        QMessageBox::information(nullptr, "white win, black lose", "white win, black lose");
        emit(loseSig(false));
    }
    if (!whiteKing) {
        QMessageBox::information(nullptr, "black win, white lose", "black win, white lose");
        emit(loseSig(true));
    }

}

void MainWindow::sendStatus() {
    statusRead = false;
    ui->lcd->display(60);
    timer->stop();
    oneSec->stop();
    QByteArray* array = new QByteArray;
    array->clear();
    if (nowOn)
        array->append("true\n");
    else {
        array->append("false\n");
    }
    array->append(getBoardInfo());
    readWriteSocket->write(array->data());
}

void MainWindow::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(nullptr,tr("Save File"),"../filename","Text files (*.txt)");
    qDebug() <<fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr,tr("错误"),tr("打开文件失败"));
        return;
    } else {
        QTextStream textStream(&file);
        QString str = getBoardInfo();
        textStream<<str;
        file.close();
    }
}

QString MainWindow::getBoardInfo() {
    QString str;
    str += "white\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int letter = j + 1;
            int number = 8 - i;
            if (board.status[letter][number].white && board.withPiece[letter][number]) {
                str += QString::fromStdString(board.status[letter][number].name);
                str += " 1 ";
                str += char(letter + 96);
                str += QString::fromStdString(std::to_string(number));
                str += "\n";
            }
        }
    }
    str += "black\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int letter = j + 1;
            int number = 8 - i;
            if (!board.status[letter][number].white && board.withPiece[letter][number]) {
                str += QString::fromStdString(board.status[letter][number].name);
                str += " 1 ";
                str += char(letter + 96);
                str += QString::fromStdString(std::to_string(number));
                str += "\n";
            }
        }
    }
    return str;
}

void MainWindow::initServer() {
    listenSocket = new QTcpServer;
//    listenSocket->waitForNewConnection(-1);
    listenSocket->listen(QHostAddress(serverHostIP), quint16(serverPort.toInt()));
    connect(listenSocket, SIGNAL(newConnection()), this, SLOT(acceptNewConnection()));
}

void MainWindow::acceptNewConnection() {
    emit(connectRecv());
    QMessageBox::information(nullptr, "info", "new connection accepted");
    readWriteSocket = listenSocket->nextPendingConnection();
    connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
}

void MainWindow::connectHost() {
    readWriteSocket = new QTcpSocket;
    readWriteSocket->connectToHost(QHostAddress(clientHostIP),quint16(clientPort.toInt()));
    connect(this->readWriteSocket,SIGNAL(readyRead()),this,SLOT(recvMessage()));
}
void MainWindow::resetWithPiece() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++)
            board.withPiece[i][j] = false;
    }
}
void MainWindow::recvMessage() {
    QString info;
    info.clear();
    info += readWriteSocket->readAll();
    resetWithPiece();
    readStatus(info);
    this->update();
}

void MainWindow::on_actionSave_triggered()
{
    saveToFile();
}

void MainWindow::setInfo(QString IP, QString port) {
    serverHostIP = IP;
    serverPort = port;
    initServer();
}

void MainWindow::setClientInfo(QString IP, QString port) {
    clientHostIP = IP;
    clientPort = port;
    connectHost();
}

void MainWindow::startListen() {
    listenSocket->waitForNewConnection();
}
void MainWindow::stopListen() {
    listenSocket->close();
}

void MainWindow::on_actionInitServer_triggered()
{
    myID = true;
    ui->label->setText("White");
    ServerSet* dialog = new ServerSet;
    connect(this, SIGNAL(connectRecv()), dialog, SLOT(received()));
    connect(dialog, SIGNAL(InfoChanged(QString, QString)), this, SLOT(setInfo(QString, QString)));
    connect(dialog, SIGNAL(okListen()), this, SLOT(startListen()));
    connect(dialog, SIGNAL(notListen()), this, SLOT(stopListen()));
    dialog->show();
}

void MainWindow::on_actionConnectToServer_triggered()
{
    myID = false;
    ui->label->setText("Black");
    connectTo* dialog = new connectTo;
//    connect(this, SIGNAL(connectRecv()), dialog, SLOT(clientreceived()));
    connect(dialog, SIGNAL(InfoChanged(QString, QString)), this, SLOT(setClientInfo(QString, QString)));
    dialog->show();
}

void MainWindow::on_actionNewGame_triggered()
{
    timer->start(60000);
    oneSec->start(1000);
    board.initWithPiece();
    QFile file(":/NewGame.txt");
    if (file.open(QFile::ReadOnly)) {
        readStatus(file);
        fileRead = true;
        this->update();
        sendStatus();
    } else {
        qDebug()<<"file open failed";
    }
}
