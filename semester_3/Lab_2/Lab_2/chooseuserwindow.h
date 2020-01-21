#ifndef CHOOSEUSERWINDOW_H
#define CHOOSEUSERWINDOW_H

#include "student.h"
#include <QDialog>
#include <vector>

namespace Ui {
class ChooseUserWindow;
}

class ChooseUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseUserWindow(QWidget *parent = nullptr, std::vector <Student*> students = {});
    ~ChooseUserWindow();

private:
    Ui::ChooseUserWindow *ui;
};

#endif // CHOOSEUSERWINDOW_H
