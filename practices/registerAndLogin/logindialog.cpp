#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

LoginData LoginDialog::loginData() {
    LoginData data;
    data.login = ui->loginEl->text();
    data.password = ui->passEl->text();
    return data;
}
