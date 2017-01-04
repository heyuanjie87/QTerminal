#include "SSWorker.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "SendSave.h"

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

SSWorker::SSWorker(SendSave *parent)
{
    ui = parent;
}

SSWorker::~SSWorker()
{
    delete dbSS;
    delete query;
}

bool SSWorker::dbInit()
{
    dbSS = new QSqlDatabase;

    *dbSS = QSqlDatabase::addDatabase("QSQLITE");
    dbSS->setDatabaseName("save.dblite");
    if (dbSS->open())
    {
       query = new QSqlQuery(*dbSS);
       return true;
    }

    return false;
}

void SSWorker::dbNewTable()
{
    QString str = "CREATE TABLE  sendlist"
                  "("
                     "sn VARCHAR,"
                     "name VARCHAR,"
                     "type VARCHAR,"
                     "value VARCHAR,"
                     "endline VARCHAR"
                  ");";

    query->exec(str);
}

void SSWorker::dbAddRow(QString &sn, QString &name, QString &type, QString &value, QString &endline)
{
    QString str;
    ostringstream tmp;

    tmp << "INSERT INTO sendlist VALUES("
        << "'" << sn.toStdString() << "',"
        << "'" << name.toStdString() << "',"
        << "'" << type.toStdString() << "',"
        << "'" << value.toStdString() << "',"
        << "'" << endline.toStdString() << "'"
        << ");";

    str = QString::fromStdString(tmp.str());

    query->exec(str);
}

void SSWorker::dbUpdateRow(QString &sn, int col, QString &val)
{
    string head = "UPDATE sendlist SET ";
    QString str;
    ostringstream temp;

    temp << head;

    switch (col)
    {
    case 0:
        temp << "name = '" << val.toStdString()  << "'";
        break;
    case 1:
        temp << "value = '" << val.toStdString() << "'";
        break;
    case 2:
        temp << "endline = '" << val.toStdString() << "'";
        break;
    default:
        break;
    }

    temp << " WHERE sn = '" << sn.toStdString() << "'";

    str = str.fromStdString(temp.str());
    query->prepare(str);

    query->exec();
}

void SSWorker::dbDelAll()
{
    string head = "DELETE FROM sendlist;";
    QString str;
    ostringstream temp;

    temp << head;
    str = str.fromStdString(temp.str());
    query->exec(str);
}

void SSWorker::dbQuery()
{
    query->exec("SELECT * FROM sendlist;");

    while(query->next())
    {
        QString name;
        QString type;
        QString value;
        QString endline;

        name = query->value(1).toString();
        type = query->value(2).toString();
        value = query->value(3).toString();
        endline = query->value(4).toString();

        ui->tableAddRow(name, type, value, endline);
    }
}

void SSWorker::run()
{
    dbInit();
    dbNewTable();
    dbQuery();
}
