/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *submitedCode;
    QTextBrowser *Remarks;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *OkButton;
    QPushButton *WrongCodeButton;
    QPushButton *UnaceptableBehaviourButton;
    QPushButton *SendMessageButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        submitedCode = new QListWidget(centralwidget);
        submitedCode->setObjectName(QString::fromUtf8("submitedCode"));

        horizontalLayout->addWidget(submitedCode);

        Remarks = new QTextBrowser(centralwidget);
        Remarks->setObjectName(QString::fromUtf8("Remarks"));

        horizontalLayout->addWidget(Remarks);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        OkButton = new QPushButton(centralwidget);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));

        horizontalLayout_2->addWidget(OkButton);

        WrongCodeButton = new QPushButton(centralwidget);
        WrongCodeButton->setObjectName(QString::fromUtf8("WrongCodeButton"));

        horizontalLayout_2->addWidget(WrongCodeButton);

        UnaceptableBehaviourButton = new QPushButton(centralwidget);
        UnaceptableBehaviourButton->setObjectName(QString::fromUtf8("UnaceptableBehaviourButton"));

        horizontalLayout_2->addWidget(UnaceptableBehaviourButton);

        SendMessageButton = new QPushButton(centralwidget);
        SendMessageButton->setObjectName(QString::fromUtf8("SendMessageButton"));

        horizontalLayout_2->addWidget(SendMessageButton);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        OkButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        WrongCodeButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        UnaceptableBehaviourButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        SendMessageButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
