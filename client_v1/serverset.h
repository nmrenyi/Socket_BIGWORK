#ifndef SERVERSET_H
#define SERVERSET_H

#include <QDialog>
#include <QString>

namespace Ui {
class ServerSet;
}

class ServerSet : public QDialog
{
    Q_OBJECT

public:
    explicit ServerSet(QWidget *parent = nullptr);
    ~ServerSet();
signals:
    void InfoChanged(QString, QString);
    void okListen();
    void notListen();
private slots:
    void on_buttonBox_accepted();
    void received();
    void on_buttonBox_rejected();

private:
    Ui::ServerSet *ui;
};

#endif // SERVERSET_H
