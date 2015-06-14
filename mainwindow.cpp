#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    motionEstimation();
    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
