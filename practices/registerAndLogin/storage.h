#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>

#include <user.h>
#include <registerdialog.h>
#include <logindialog.h>

class Storage : public QObject
{
    QSqlDatabase db;

    Q_OBJECT
public:
    explicit Storage(QString path, QObject *parent = nullptr);

    bool open();
    void close();

    User * registerUser(RegisterData & data);
    User * loginUser(LoginData & data);

signals:

public slots:
};

#endif // STORAGE_H
