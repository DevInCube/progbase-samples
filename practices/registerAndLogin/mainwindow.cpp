#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <registerdialog.h>
#include <logindialog.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "./db.db";
    _storage = new Storage(path);
    if (!_storage->open()) {
        // @todo error
    }
}

MainWindow::~MainWindow()
{
    _storage->close();
    delete _storage;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    RegisterDialog dialog(this);
    int res = dialog.exec();
    if (res == QDialog::Accepted) {
        RegisterData data = dialog.registerData();
        try {
            User * user = _storage->registerUser(data);
            //
        } catch (const QSqlError & err) {
            QMessageBox::critical(this, "register", err.text());
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    LoginDialog dialog(this);
    int res = dialog.exec();
    if (res == QDialog::Accepted) {
        LoginData data = dialog.loginData();
        User * user = _storage->loginUser(data);
        if (user == nullptr) {
            QMessageBox::critical(this, "login", "no user");
        } else {
            QString info = "User: " + QString::number(user->id) + " " + QString::number(user->role);
            QMessageBox::information(this, "login", info);
        }
    }
}
