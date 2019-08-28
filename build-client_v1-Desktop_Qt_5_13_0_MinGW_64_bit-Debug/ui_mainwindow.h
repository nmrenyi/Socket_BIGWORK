/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionReadFile;
    QAction *actionSave;
    QAction *actionInitServer;
    QAction *actionConnectToServer;
    QAction *actionNewGame;
    QWidget *centralWidget;
    QLCDNumber *lcd;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuStart;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(854, 747);
        actionReadFile = new QAction(MainWindow);
        actionReadFile->setObjectName(QString::fromUtf8("actionReadFile"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionInitServer = new QAction(MainWindow);
        actionInitServer->setObjectName(QString::fromUtf8("actionInitServer"));
        actionConnectToServer = new QAction(MainWindow);
        actionConnectToServer->setObjectName(QString::fromUtf8("actionConnectToServer"));
        actionNewGame = new QAction(MainWindow);
        actionNewGame->setObjectName(QString::fromUtf8("actionNewGame"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lcd = new QLCDNumber(centralWidget);
        lcd->setObjectName(QString::fromUtf8("lcd"));
        lcd->setGeometry(QRect(740, 50, 101, 91));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(740, 170, 81, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 854, 21));
        menuStart = new QMenu(menuBar);
        menuStart->setObjectName(QString::fromUtf8("menuStart"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuStart->menuAction());
        menuStart->addAction(actionInitServer);
        menuStart->addAction(actionConnectToServer);
        mainToolBar->addAction(actionNewGame);
        mainToolBar->addAction(actionReadFile);
        mainToolBar->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionReadFile->setText(QCoreApplication::translate("MainWindow", "ReadFile", nullptr));
#if QT_CONFIG(shortcut)
        actionReadFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionInitServer->setText(QCoreApplication::translate("MainWindow", "InitServer", nullptr));
        actionConnectToServer->setText(QCoreApplication::translate("MainWindow", "ConnectToServer", nullptr));
        actionNewGame->setText(QCoreApplication::translate("MainWindow", "NewGame", nullptr));
        label->setText(QString());
        menuStart->setTitle(QCoreApplication::translate("MainWindow", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
