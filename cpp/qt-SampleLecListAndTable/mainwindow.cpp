#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    ui->listWidget->addItem(text);
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    qDebug() << "changed!";
    auto items = ui->listWidget->selectedItems();
    auto hasSelected = items.size() > 0;
    if (hasSelected) {
        auto text = items[0]->text();
        ui->label->setText(text);
    }
    ui->pushButton_2->setEnabled(hasSelected);
}

void MainWindow::on_pushButton_2_clicked()
{
    QList items = ui->listWidget->selectedItems();
    auto hasSelected = items.size() > 0;
    if (hasSelected) {
        delete ui->listWidget->takeItem(ui->listWidget->row(items[0]));
    }
}
