#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QWidget>


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
        newUserAction = new QAction(tr("New User"), this);
        openUserAction = new QAction(tr("Open User File"), this);

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
        userMenu = menuBar()->addMenu(tr("User"));
        userMenu->addAction(newUserAction);
        userMenu->addAction(openUserAction);
        setWindowTitle(tr("My Little Checker"));

        freopen("student.txt", "r", stdin);
        std::cin >> numberStudents;
        students.resize(numberStudents);
        for(int i = 0; i < numberStudents; i++){
            //std:string buffer;
           // std::cin >> buffer;
            //students[i]->name = QString::fromStdString(buffer);
        }



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

void MainWindow::newUser()
{

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
