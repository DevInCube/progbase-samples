#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

RegisterData RegisterDialog::registerData() {
    RegisterData data;
    data.login = ui->loginEl->text();
    data.password = ui->passEl->text();
    return data;
}
