#include "storage.h"
#include <QCryptographicHash>
#include <QVariant>

Storage::Storage(QString path, QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

User * Storage::registerUser(RegisterData & data) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password_hash) VALUES (:login, :hash)");
    query.bindValue(":login", data.login);
    // @todo hash pass
    QByteArray hashArray = QCryptographicHash::hash(data.password.toUtf8(), QCryptographicHash::Md5);
    QString passwordHash = QString(hashArray.toHex());
    query.bindValue(":hash", passwordHash);
    if (!query.exec()) {
        throw query.lastError();
    }
    User * user = new User();
    user->id = query.lastInsertId().value<int>();
    user->login = data.login;
    user->role = UserRole::SimpleUser;
    return user;
}

User * Storage::loginUser(LoginData & data) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE login = :login AND password_hash = :hash");
    query.bindValue(":login", data.login);
    QByteArray hashArray = QCryptographicHash::hash(data.password.toUtf8(), QCryptographicHash::Md5);
    QString passwordHash = QString(hashArray.toHex());
    query.bindValue(":hash", passwordHash);
    if (!query.exec()) {
        throw query.lastError();
    }
    if (query.next()) {
       User * user = new User();
       user->id = query.value("id").toInt();
       user->login = query.value("login").toString();
       user->role = (UserRole)query.value("role").toInt();
       return user;
    }
    return nullptr;
}

bool Storage::open() {
    return db.open();
}

void Storage::close() {
    db.close();
}
