#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPainter>
#include <QPixmap>
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

private slots:
    void on_actionReadFile_triggered();

private:
    Ui::MainWindow *ui;
    const int startx = 100;
    const int starty = 100;
    const int interval = 80;
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

};

#endif // MAINWINDOW_H
