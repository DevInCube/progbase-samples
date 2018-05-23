#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

struct RegisterData {
    QString login;
    QString password;
};

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

    RegisterData registerData();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
