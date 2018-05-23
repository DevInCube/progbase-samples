#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

struct LoginData {
    QString login;
    QString password;
};

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    LoginData loginData();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
