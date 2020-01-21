/********************************************************************************
** Form generated from reading UI file 'chooseuserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEUSERWINDOW_H
#define UI_CHOOSEUSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChooseUserWindow
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *studentListWidget;

    void setupUi(QDialog *ChooseUserWindow)
    {
        if (ChooseUserWindow->objectName().isEmpty())
            ChooseUserWindow->setObjectName(QString::fromUtf8("ChooseUserWindow"));
        ChooseUserWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(ChooseUserWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        studentListWidget = new QListWidget(ChooseUserWindow);
        studentListWidget->setObjectName(QString::fromUtf8("studentListWidget"));

        verticalLayout->addWidget(studentListWidget);


        retranslateUi(ChooseUserWindow);

        QMetaObject::connectSlotsByName(ChooseUserWindow);
    } // setupUi

    void retranslateUi(QDialog *ChooseUserWindow)
    {
        ChooseUserWindow->setWindowTitle(QApplication::translate("ChooseUserWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseUserWindow: public Ui_ChooseUserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEUSERWINDOW_H
