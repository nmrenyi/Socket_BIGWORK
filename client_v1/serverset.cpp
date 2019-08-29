#include "serverset.h"
#include "ui_serverset.h"
#include <QDebug>
#include <QMessageBox>
#include <string>
#include <sstream>

ServerSet::ServerSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSet)
{
    ui->setupUi(this);
    ui->wait->setVisible(false);
//    ui->hostIP->setText("127.0.0.1");
    ui->port->setText("8888");
}

ServerSet::~ServerSet()
{
    delete ui;
}
bool checkIP(QString IP, QString port) {
    int dots = 0;
    for (auto x : IP)
        if (x == '.')
            dots++;
    qDebug() << "dots = " << dots;
    if (dots != 3)
        return false;
    IP += ".";
    std::istringstream is(IP.toStdString());
    std::string token;
    while(std::getline(is, token, '.')) {
        QString qs = QString::fromStdString(token);
        qDebug() << "qs = " << qs;
        bool flag = true;
        int num = qs.toInt(&flag, 10);
        qDebug() << "num = " << num;
        qDebug() << "flag = " << flag;
        if (!flag)
            return false;
        if (num < 0 || num > 255)
            return false;
    }
    int portNum = port.toInt();
    qDebug () << "port = " << port;
    if (portNum < 0 || portNum > 65535)
        return false;
    return true;
}

void ServerSet::on_buttonBox_accepted()
{
    QString nowIP = ui->hostIP->text();
    QString nowPort = ui->port->text();
    if (!checkIP(nowIP, nowPort)) {
        QMessageBox::information(this, "not available IP or port", "not available IP or port");
        return;
    }

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
