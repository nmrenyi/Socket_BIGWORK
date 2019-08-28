/********************************************************************************
** Form generated from reading UI file 'serverset.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSET_H
#define UI_SERVERSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ServerSet
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *wait;
    QLabel *label;
    QLineEdit *hostIP;
    QLabel *label_2;
    QLineEdit *port;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ServerSet)
    {
        if (ServerSet->objectName().isEmpty())
            ServerSet->setObjectName(QString::fromUtf8("ServerSet"));
        ServerSet->resize(186, 298);
        verticalLayout_3 = new QVBoxLayout(ServerSet);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wait = new QLabel(ServerSet);
        wait->setObjectName(QString::fromUtf8("wait"));
        wait->setEnabled(true);

        verticalLayout->addWidget(wait);

        label = new QLabel(ServerSet);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        hostIP = new QLineEdit(ServerSet);
        hostIP->setObjectName(QString::fromUtf8("hostIP"));

        verticalLayout->addWidget(hostIP);

        label_2 = new QLabel(ServerSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        port = new QLineEdit(ServerSet);
        port->setObjectName(QString::fromUtf8("port"));

        verticalLayout->addWidget(port);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(ServerSet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(ServerSet);

        QMetaObject::connectSlotsByName(ServerSet);
    } // setupUi

    void retranslateUi(QDialog *ServerSet)
    {
        ServerSet->setWindowTitle(QCoreApplication::translate("ServerSet", "Dialog", nullptr));
        wait->setText(QCoreApplication::translate("ServerSet", "waiting for connection...", nullptr));
        label->setText(QCoreApplication::translate("ServerSet", "Host IP", nullptr));
        label_2->setText(QCoreApplication::translate("ServerSet", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerSet: public Ui_ServerSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSET_H
