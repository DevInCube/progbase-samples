#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto outputWindow = new MainWindow2(this);
    outputWindow->show();

    connect(this, SIGNAL(message(QString)), outputWindow, SLOT(setString(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit message(ui->lineEdit->text());
}
