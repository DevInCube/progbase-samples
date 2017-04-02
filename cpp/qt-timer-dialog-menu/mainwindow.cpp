#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerUpdate()));
    timer->start(1000);

    ui->actionNew_file->setShortcuts(QKeySequence::New);
    ui->actionNew_file->setStatusTip(tr("Create a new file"));
    connect(ui->actionNew_file, &QAction::triggered, this, &MainWindow::newFile);
}

void MainWindow::newFile()
{
    qDebug() << "New File!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimerUpdate()
{
    qDebug() << "timer updated!";
}

void MainWindow::on_pushButton_clicked()
{
    QListWidget * listWidget = ui->listWidget;

    QLineEdit * input = this->findChild<QLineEdit *>("lineEdit");
    QString inputText = input->text();

    listWidget->addItem(inputText);
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    Dialog dialog;
    dialog.setWindowTitle("A title!");
    QString dataStr("hi!");
    dialog.setData(dataStr);  // user-defined method
    if (dialog.exec()) {
        qDebug() << "Accepted!";
    } else {
        qDebug() << "Rejected!";
    }
}
