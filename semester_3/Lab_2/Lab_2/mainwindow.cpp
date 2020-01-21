#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QWidget>
#include <string>
#include <fstream>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTableWidgetItem* emptyItem = new QTableWidgetItem("No program is chosen.");
    ui->submitedCode->setItem(0,0,emptyItem);
    openAction = new QAction(tr("Open"), this);
        saveAction = new QAction(tr("Save"), this);
        exitAction = new QAction(tr("Exit"), this);
        newUserAction = new QAction(tr("New Student"), this);
        openUserAction = new QAction(tr("Open by Student"), this);

        connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
        connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
        connect(newUserAction, SIGNAL(triggered()), this, SLOT(newUser()));
        connect(openUserAction, SIGNAL(triggered()), this, SLOT(openUser()));
        connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        fileMenu = menuBar()->addMenu(tr("File"));
        fileMenu->addAction(openAction);
        fileMenu->addAction(saveAction);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAction);
        userMenu = menuBar()->addMenu(tr("Student"));
        userMenu->addAction(newUserAction);
        userMenu->addAction(openUserAction);
        setWindowTitle(tr("My Little Checker"));

        std::ifstream infile("../Lab_2/students.txt", std::ios::in);
        std::string buffer;
        infile >> numberStudents;
        getline(infile, buffer);//skip \n
        for(int i = 0; i < numberStudents; i++){
            students.push_back(new Student());
            getline(infile,buffer);
            std::cout << buffer << std::endl;
            students[i]->name = QString::fromStdString(buffer);

            getline(infile,buffer);
            students[i]->group = QString::fromStdString(buffer);

            getline(infile,buffer);
            students[i]->organization = QString::fromStdString(buffer);

            getline(infile,buffer);
            students[i]->contact = QString::fromStdString(buffer);

        }
        infile.close();


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "");//tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        ui->submitedCode->clear();
        ui->submitedCode->setRowCount(0);
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        QString fileInsides = in.readAll();
        int len = fileInsides.length();
        QString currentLine = "";
        QTableWidgetItem* currentLineItem;
        int lineNumber = 0;
        for(int i = 0; i < len; i++)
            if(fileInsides[i] == '\n')
                lineNumber++;
        ui->submitedCode->setRowCount(lineNumber);
        lineNumber = 0;
        for(int i = 0; i < len; i++){
            if(fileInsides[i] == '\n'){
                currentLineItem = new QTableWidgetItem(currentLine);
                ui->submitedCode->setItem(0,lineNumber,currentLineItem);
                lineNumber++;
                currentLine = "";
            }
            else
                currentLine += fileInsides[i];
        }
        file.close();
        anyFileOpened = true;
        lineComments.resize(lineNumber, "");
        lineComments[0] = "Hel lo!";
    }
}

void MainWindow::save()
{
    if(anyFileOpened){
        lineComments[currentLineId] = ui->currentLineComment->toPlainText().toStdString();
    }

}

void MainWindow::quit()
{

}

void MainWindow::saveStudents(){
    std::ofstream file;
    file.open("../Lab_2/students.txt", std::ios::out);
    file.clear();
    file << numberStudents << std::endl;
    for(int i = 0; i < numberStudents; i++){
        file << students[i]->name.toStdString() << std::endl;
        file << students[i]->group.toStdString() << std::endl;
        file << students[i]->organization.toStdString() << std::endl;
        file << students[i]->contact.toStdString() << std::endl;
    }
}

void MainWindow::newUser()
{
    NewUserWindow window;
    window.setModal(true);
    window.exec();
    if(window.result()){
        newStudent = window.getNewStudent();
        QTableWidgetItem* newName = new QTableWidgetItem(newStudent->name);
        ui->submitedCode->setItem(0,0, newName);
        students.push_back(newStudent);
        numberStudents++;
        saveStudents();
    }
}

void MainWindow::openUser()
{

}

void MainWindow::on_submitedCode_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_submitedCode_itemClicked(QTableWidgetItem *item)
{
    if(currentLineId >= 0){
        std::string stringToSave = ui->currentLineComment->toPlainText().toStdString();
        lineComments[currentLineId] = stringToSave;
        if(stringToSave.size() > 0)
            ui->submitedCode->item(currentLineId,0)->setBackgroundColor(Qt::yellow);
        ui->currentLineComment->clear();
    }
    currentLineId = ui->submitedCode->row(item);
    QString currentComment = QString::fromStdString(lineComments[currentLineId]);
    ui->currentLineComment->setText(currentComment);
}
