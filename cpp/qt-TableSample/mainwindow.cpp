#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto table = ui->tableWidget;
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList{"#", "Name", "Text"});
    table->verticalHeader()->hide();
    table->setShowGrid(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->setStyleSheet("QTableView {selection-background-color: red;}");  // you can use CSS
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    auto table = ui->tableWidget;
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(ui->lineEdit->text()));
    table->setItem(row, 1, new QTableWidgetItem("Do"));
    table->setItem(row, 2, new QTableWidgetItem("It"));
}

void MainWindow::on_pushButton_2_clicked()
{
    auto table = ui->tableWidget;
    auto items = table->selectedItems();
    auto hasItems = (items.size() > 0);
    if (hasItems) {
        auto item = items[0];
        table->removeRow(table->row(item));
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    qDebug() << row << " | " << column;
}
