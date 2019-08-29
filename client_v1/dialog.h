#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void closeEvent(QCloseEvent*);
    Ui::Dialog *ui;
private slots:
    void on_buttonBox_accepted();
signals:
    void selected(int);
};

#endif // DIALOG_H
