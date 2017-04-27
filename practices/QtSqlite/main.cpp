#include <iostream>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

using namespace std;

// http://blog.davidecoppola.com/2016/11/howto-embed-database-in-application-with-sqlite-and-qt/

int main(void)
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) {
        qDebug() << "sqlite not available";
        return 1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(":memory:");
    if(!db.open()) {
        qDebug() << "ERROR: " << db.lastError();
        return 1;
    }

    QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");
    if(!query.isActive()){
        qDebug() << "ERROR: " << query.lastError().text();
        return 1;
    }

    query = QSqlQuery("INSERT INTO people values (1, 'TEXT-1')");
    if(!query.isActive()){
        qDebug() << "ERROR: " << query.lastError().text();
        return 1;
    }
    QSqlQuery("INSERT INTO people values (2, 'TEXT-2')");

    query = QSqlQuery("SELECT * FROM people");
    if(!query.exec()){
        qDebug() << "ERROR: " << query.lastError().text();
    }

    // prepared statements
//    QSqlQuery query;
//    query.prepare("SELECT name FROM people WHERE id = ?");
//    query.addBindValue(mInputText->text().toInt());

    // if (!query.first()) // test for records

    while(query.next())
    {
        // access fields of current record
         qDebug() << query.value(0).toString() << " | " << query.value(1).toString();
    }

    // @todo remove
    QSqlQuery("DELETE FROM people WHERE id = 1");

    qDebug() << "After remove:";

    query = QSqlQuery("SELECT * FROM people");
    query.exec();
    while(query.next())
    {
        // access fields of current record
         qDebug() << query.value(0).toString() << " | " << query.value(1).toString();
    }

    cout << "End."  << endl;

    return 0;
}
