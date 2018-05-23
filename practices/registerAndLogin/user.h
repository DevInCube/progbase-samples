#ifndef USER_H
#define USER_H

#include <QObject>

enum UserRole {
    SimpleUser,
    Admin
};

class User : public QObject
{
    Q_OBJECT
public:
    int id;
    QString login;
    UserRole role;

    explicit User(QObject *parent = nullptr);



signals:

public slots:
};

#endif // USER_H
