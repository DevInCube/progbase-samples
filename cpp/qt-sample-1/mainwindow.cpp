#include <QDebug>
#include <QCloseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "student.h"

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
    QLineEdit * nameEdit = this->findChild<QLineEdit*>("nameLineEdit");
    QLineEdit * surnameEdit = this->findChild<QLineEdit*>("surnameLineEdit");
    QSpinBox * ageBox = this->findChild<QSpinBox*>("spinBox");

    QString name = nameEdit->text();
    QString surname = surnameEdit->text();
    int age = ageBox->value();

    student * newStudent = new student;
    newStudent->set_name(name.toStdString());
    newStudent->set_surname(surname.toStdString());
    newStudent->set_age(age);

    this->students.push_back(newStudent);

    qDebug() << this->students.size();
    for (student * st : students) {
        st->print();
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    // use this to cleanup allocated memory

    for (student * st : students) {
        delete st;
    }
    qDebug() << "Window closed!";
    event->accept();
}
