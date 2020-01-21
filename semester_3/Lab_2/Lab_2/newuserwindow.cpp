#include "newuserwindow.h"
#include "ui_newuserwindow.h"

NewUserWindow::NewUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Add new Student"));
}

NewUserWindow::~NewUserWindow()
{
    delete ui;
}

Student* NewUserWindow::getNewStudent(){
    return newStudent;
}

void NewUserWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    QString _name = ui->nameText->toPlainText();
    QString _group = ui->groupText->toPlainText();
    QString _org = ui->orgText->toPlainText();
    QString _contact = ui->contactText->toPlainText();

    newStudent = new Student(_name, _group, _org, _contact);
}
