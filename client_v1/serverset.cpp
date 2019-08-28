#include "serverset.h"
#include "ui_serverset.h"
#include <QDebug>
#include <QMessageBox>

ServerSet::ServerSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSet)
{
    ui->setupUi(this);
    ui->wait->setVisible(false);
}

ServerSet::~ServerSet()
{
    delete ui;
}

void ServerSet::on_buttonBox_accepted()
{
    QString nowIP = ui->hostIP->text();
    QString nowPort = ui->port->text();
//    if (!checkIP(nowIP, nowPort)) {
//        QMessageBox::information(this, "not available IP or port");
//        return;
//    }

   QString hostIP = ui->hostIP->text();
   QString port = ui->port->text();
   emit(InfoChanged(hostIP, port));
   emit(okListen());
   ui->wait->setVisible(true);
}

void ServerSet::on_buttonBox_rejected()
{
    ui->wait->setVisible(false);
    emit(notListen());
}

void ServerSet::received() {
//    QMessageBox::information(nullptr, "success", "you've connected to server");
    this->accept();
}
