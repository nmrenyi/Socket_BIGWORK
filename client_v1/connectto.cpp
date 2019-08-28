#include "connectto.h"
#include "ui_connectto.h"
#include <QMessageBox>
#include <QDebug>

connectTo::connectTo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectTo)
{
    ui->setupUi(this);
    ui->connecting->setVisible(false);
}

connectTo::~connectTo()
{
    delete ui;
}

void connectTo::on_buttonBox_accepted()
{
    QString hostIP = ui->hostIP->text();
    QString port = ui->port->text();
    emit(InfoChanged(hostIP, port));
    ui->connecting->setVisible(true);
    this->accept();
}

void connectTo::clientreceived() {
    qDebug() << "here client received";
    this->accept();
    QMessageBox::information(nullptr, "success", "you've connected to the server");
}
