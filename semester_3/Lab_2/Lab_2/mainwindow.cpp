#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->submitedCode->addItem("No program is chosen.");
    openAction = new QAction(tr("&Open"), this);
        saveAction = new QAction(tr("&Save"), this);
        exitAction = new QAction(tr("E&xit"), this);

        connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
        connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
        connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(openAction);
        fileMenu->addAction(saveAction);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAction);
        setWindowTitle(tr("Notepad"));
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
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        QString file_insides = in.readAll();
        int len = file_insides.length();
        QString current_line = "";
        int cnt = 0;
        for(int i = 0; i < len; i++){
            if(file_insides[i] == '\n'){
                ui->submitedCode->addItem(current_line);
                //std::cout << current_line.toStdString() + std::to_string(cnt) + "\n";
                cnt++;
                current_line = "";
            }
            else
                current_line += file_insides[i];
        }
        file.close();
        any_file_opened = true;
    }
}

void MainWindow::save()
{

}

void MainWindow::quit()
{

}

void MainWindow::on_submitedCode_itemClicked(QListWidgetItem *item)
{
    if(any_file_opened)
        std::cout << ui->submitedCode->row(item) << std::endl;
}
