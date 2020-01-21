/********************************************************************************
** Form generated from reading UI file 'newuserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSERWINDOW_H
#define UI_NEWUSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_NewUserWindow
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *nameText;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *groupText;
    QLabel *label_3;
    QTextEdit *orgText;
    QLabel *label_4;
    QTextEdit *contactText;

    void setupUi(QDialog *NewUserWindow)
    {
        if (NewUserWindow->objectName().isEmpty())
            NewUserWindow->setObjectName(QString::fromUtf8("NewUserWindow"));
        NewUserWindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(NewUserWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        nameText = new QTextEdit(NewUserWindow);
        nameText->setObjectName(QString::fromUtf8("nameText"));
        nameText->setGeometry(QRect(100, 20, 261, 31));
        label = new QLabel(NewUserWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 71, 20));
        label_2 = new QLabel(NewUserWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 141, 21));
        groupText = new QTextEdit(NewUserWindow);
        groupText->setObjectName(QString::fromUtf8("groupText"));
        groupText->setGeometry(QRect(150, 70, 211, 31));
        label_3 = new QLabel(NewUserWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 130, 141, 20));
        orgText = new QTextEdit(NewUserWindow);
        orgText->setObjectName(QString::fromUtf8("orgText"));
        orgText->setGeometry(QRect(170, 120, 191, 31));
        label_4 = new QLabel(NewUserWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 180, 67, 17));
        contactText = new QTextEdit(NewUserWindow);
        contactText->setObjectName(QString::fromUtf8("contactText"));
        contactText->setGeometry(QRect(100, 170, 261, 31));

        retranslateUi(NewUserWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewUserWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewUserWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewUserWindow);
    } // setupUi

    void retranslateUi(QDialog *NewUserWindow)
    {
        NewUserWindow->setWindowTitle(QApplication::translate("NewUserWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("NewUserWindow", "\320\206\320\274'\321\217:", nullptr));
        label_2->setText(QApplication::translate("NewUserWindow", "\320\235\320\260\320\262\321\207\320\260\320\273\321\214\320\275\320\260 \320\263\321\200\321\203\320\277\320\260:", nullptr));
        label_3->setText(QApplication::translate("NewUserWindow", "\320\235\320\260\320\262\321\207\320\260\320\273\321\214\320\275\320\270\320\271 \320\267\320\260\320\272\320\273\320\260\320\264:", nullptr));
        label_4->setText(QApplication::translate("NewUserWindow", "\320\232\320\276\320\275\321\202\320\260\320\272\321\202:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewUserWindow: public Ui_NewUserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSERWINDOW_H
