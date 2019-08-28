#include "connectto.h"
#include "ui_connectto.h"
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <sstream>
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
bool checkClientIP(QString IP, QString port) {
    int dots = 0;
    for (auto x : IP)
        if (x == '.')
            dots++;
    if (dots != 3)
        return false;
    IP += ".";
    std::istringstream is(IP.toStdString());
    std::string token;
    while(std::getline(is, token, '.')) {
        QString qs = QString::fromStdString(token);
        bool flag = true;
        int num = qs.toInt(&flag, 10);
        if (!flag)
            return false;
        if (num < 0 || num > 255)
            return false;
    }
    int portNum = port.toInt();
    qDebug() << "port = " << portNum;
    if (portNum < 0 || portNum > 65535)
        return false;
    return true;
}

void connectTo::on_buttonBox_accepted()
{
    QString hostIP = ui->hostIP->text();
    QString port = ui->port->text();
    if (!checkClientIP(hostIP, port)) {
        QMessageBox::information(this, "not available IP or port", "not available IP or port");
        return;
    }

    emit(InfoChanged(hostIP, port));
    ui->connecting->setVisible(true);
    this->accept();
}

void connectTo::clientreceived() {
    qDebug() << "here client received";
    this->accept();
    QMessageBox::information(nullptr, "success", "you've connected to the server");
}
