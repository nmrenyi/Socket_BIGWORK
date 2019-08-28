#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPainter>
#include <QtNetwork>
#include <QPixmap>
#include <QTime>
#include <piece.h>
#include <board.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Board board;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    int choice = -1;
    void initServer();
    void connectHost();
private slots:
    void acceptNewConnection();
    void recvMessage();
    void on_actionReadFile_triggered();
    void setIt(int);
    void on_actionSave_triggered();
    void setInfo(QString, QString);
    void setClientInfo(QString, QString);
    void on_actionInitServer_triggered();
    void startListen();
    void on_actionConnectToServer_triggered();
    void stopListen();
    void on_actionNewGame_triggered();
    void minus();

    void LOSE(bool);

private:
    bool myID;
    bool nowOn;
    bool statusRead;
    int nowTime;
    const int timeLimit = 60;
    QTimer* timer;
    Ui::MainWindow *ui;
    QTcpServer* listenSocket;
    QTcpSocket* readWriteSocket;
    const int startx = 100;
    const int starty = 100;
    const int interval = 80;
    QString clientHostIP;
    QString serverHostIP;
    QString clientPort;
    QString serverPort;
    bool fileRead;
    QPixmap black_bishop;
    QPixmap black_king;
    QPixmap black_knight;
    QPixmap black_pawn;
    QPixmap black_queen;
    QPixmap black_rook;
    QPixmap white_bishop;
    QPixmap white_king;
    QPixmap white_knight;
    QPixmap white_pawn;
    QPixmap white_queen;
    QPixmap white_rook;
    void saveToFile();
    QString getBoardInfo();
    void sendStatus();
    void readStatus(QString);
    void readStatus(QFile&);
    void resetWithPiece();
    void checkKing();
signals:
    void connectRecv();
    void loseSig(bool);

};

#endif // MAINWINDOW_H
