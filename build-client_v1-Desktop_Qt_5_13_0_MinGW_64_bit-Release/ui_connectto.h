/********************************************************************************
** Form generated from reading UI file 'connectto.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTTO_H
#define UI_CONNECTTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_connectTo
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *connecting;
    QLabel *label;
    QLineEdit *hostIP;
    QLabel *label_2;
    QLineEdit *port;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *connectTo)
    {
        if (connectTo->objectName().isEmpty())
            connectTo->setObjectName(QString::fromUtf8("connectTo"));
        connectTo->resize(466, 393);
        verticalLayout_3 = new QVBoxLayout(connectTo);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        connecting = new QLabel(connectTo);
        connecting->setObjectName(QString::fromUtf8("connecting"));

        verticalLayout->addWidget(connecting);

        label = new QLabel(connectTo);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        hostIP = new QLineEdit(connectTo);
        hostIP->setObjectName(QString::fromUtf8("hostIP"));

        verticalLayout->addWidget(hostIP);

        label_2 = new QLabel(connectTo);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        port = new QLineEdit(connectTo);
        port->setObjectName(QString::fromUtf8("port"));

        verticalLayout->addWidget(port);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(connectTo);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(connectTo);
        QObject::connect(buttonBox, SIGNAL(rejected()), connectTo, SLOT(reject()));

        QMetaObject::connectSlotsByName(connectTo);
    } // setupUi

    void retranslateUi(QDialog *connectTo)
    {
        connectTo->setWindowTitle(QCoreApplication::translate("connectTo", "Dialog", nullptr));
        connecting->setText(QCoreApplication::translate("connectTo", "connecting to server...", nullptr));
        label->setText(QCoreApplication::translate("connectTo", "Host IP", nullptr));
        label_2->setText(QCoreApplication::translate("connectTo", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connectTo: public Ui_connectTo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTTO_H
