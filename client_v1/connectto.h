#ifndef CONNECTTO_H
#define CONNECTTO_H

#include <QDialog>
#include <QString>

namespace Ui {
class connectTo;
}

class connectTo : public QDialog
{
    Q_OBJECT

public:
    explicit connectTo(QWidget *parent = nullptr);
    ~connectTo();

private slots:
    void on_buttonBox_accepted();
    void clientreceived();
signals:
    void InfoChanged(QString, QString);
private:
    Ui::connectTo *ui;
};

#endif // CONNECTTO_H
