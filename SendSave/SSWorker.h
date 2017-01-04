#ifndef SSWORKER_H
#define SSWORKER_H

#include <QThread>

class QSqlDatabase;
class SendSave;
class QSqlQuery;

class SSWorker : public QThread
{
public:
    SSWorker(SendSave *parent);
    ~SSWorker();

private:
    void run();

    bool dbInit();
    void dbNewTable();
    void dbQuery();

public:
    void dbAddRow(QString &sn, QString &name, QString &type, QString &value, QString &endline);
    void dbUpdateRow(QString &sn, int col, QString &val);
    void dbDelAll();

private:
    QSqlDatabase *dbSS;
    SendSave *ui;
    QSqlQuery *query;
};

#endif // SSWORKER_H
