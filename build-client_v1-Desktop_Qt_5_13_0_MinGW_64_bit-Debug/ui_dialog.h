/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QRadioButton *queen;
    QRadioButton *rook;
    QRadioButton *knight;
    QRadioButton *bishop;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(80, 70, 191, 111));
        queen = new QRadioButton(groupBox);
        queen->setObjectName(QString::fromUtf8("queen"));
        queen->setGeometry(QRect(10, 20, 91, 18));
        rook = new QRadioButton(groupBox);
        rook->setObjectName(QString::fromUtf8("rook"));
        rook->setGeometry(QRect(10, 40, 91, 18));
        knight = new QRadioButton(groupBox);
        knight->setObjectName(QString::fromUtf8("knight"));
        knight->setGeometry(QRect(10, 60, 91, 18));
        bishop = new QRadioButton(groupBox);
        bishop->setObjectName(QString::fromUtf8("bishop"));
        bishop->setGeometry(QRect(10, 80, 91, 18));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "Choose your promotion", nullptr));
        queen->setText(QCoreApplication::translate("Dialog", "Queen", nullptr));
        rook->setText(QCoreApplication::translate("Dialog", "Rook", nullptr));
        knight->setText(QCoreApplication::translate("Dialog", "Knight", nullptr));
        bishop->setText(QCoreApplication::translate("Dialog", "Bishop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
