/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student.h"
#include "newuserwindow.h"
#include "chooseuserwindow.h"
#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void open();
    void save();
    void quit();
    void newUser();
    void openUser();

    void on_submitedCode_itemClicked(QListWidgetItem *item);

    void on_submitedCode_itemClicked(QTableWidgetItem *item);

private:


    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *newUserAction;
    QAction *openUserAction;

    QMenu *fileMenu;
    QMenu *userMenu;

    Ui::MainWindow *ui;

    bool anyFileOpened = false;
    int currentLineId = -1;
    int numberStudents = 0;

    std::vector <std::string> lineComments;
    std::vector <Student*> students;

    Student* newStudent = nullptr;


    void saveStudents();


};
#endif // MAINWINDOW_H
