#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QObject>
#include "NewSession/nstypes.h"

class QDomDocument;
class QDomElement;
class QFile;

class ProjectFile : public QObject
{
    Q_OBJECT
public:
    explicit ProjectFile(QObject *parent = 0);

    bool Load(QString filename);
    bool GetSessionList(SesList &sl);

    void DelSession(QString &id);
    void AddSession(Session &ses);
    void Save();
    void SetSesShow(QString &id, bool s);

signals:

public slots:

private:
    void init();
    void addParam(QDomElement &e, Session &ses);
    void getSession(QDomElement &sesEle, Session &ses);
    void getParam(QDomElement &parEle, Session &ses);
    void addType(QString &name);

private:
    QDomDocument *doc;
    QDomElement *root;
    QFile *prjfile;
};

#endif // PROJECTFILE_H
