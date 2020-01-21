#ifndef NEWUSERWINDOW_H
#define NEWUSERWINDOW_H

#include "student.h"
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class NewUserWindow;
}

class NewUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserWindow(QWidget *parent = nullptr);
    ~NewUserWindow();
    Student* getNewStudent();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::NewUserWindow *ui;
    Student* newStudent = nullptr;
};

#endif // NEWUSERWINDOW_H
