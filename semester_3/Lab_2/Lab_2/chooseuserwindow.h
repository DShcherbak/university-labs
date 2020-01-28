#ifndef CHOOSEUSERWINDOW_H
#define CHOOSEUSERWINDOW_H

#include "student.h"
#include <QDialog>
#include <vector>
#include <QListWidget>
namespace Ui {
class ChooseUserWindow;
}

class ChooseUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseUserWindow(QWidget *parent = nullptr, std::vector <Student*> students = {});
    ~ChooseUserWindow();

private slots:

    void on_studentListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ChooseUserWindow *ui;
    int chosenStudent = -1;

};

#endif // CHOOSEUSERWINDOW_H
