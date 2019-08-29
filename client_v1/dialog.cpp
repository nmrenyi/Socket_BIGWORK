#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::closeEvent(QCloseEvent *) {}

void Dialog::on_buttonBox_accepted()
{
    int promotion = 0;
    if (ui->queen->isChecked())
        promotion = 0;
    else if (ui->rook->isChecked())
        promotion = 1;
    else if (ui->bishop->isChecked())
        promotion = 2;
    else if (ui->knight->isChecked())
        promotion = 3;
//    qDebug() << promotion << "!!!!!!!!!!";
    emit(selected(promotion));
}
