#include "projectfile.h"

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>

ProjectFile::ProjectFile(QObject *parent) : QObject(parent)
{
    init();
}

bool ProjectFile::Load(QString filename)
{
    bool ret = true;

    prjfile->setFileName(filename);

    if(!prjfile->open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if(!doc->setContent(prjfile, false, &errorStr, &errorLine, &errorColumn))
    {
        return false;
    }

    prjfile->close();

    return ret;
}

void ProjectFile::getSession(QDomElement &sesEle, Session &ses)
{
    QDomNodeList list;

    ses.id = sesEle.attribute("ID");

    list = sesEle.elementsByTagName("param");
    for (int i = 0; i < list.size(); i ++)
    {
        QDomElement paramEle = list.item(i).toElement();

        getParam(paramEle, ses);
    }
}

void ProjectFile::getParam(QDomElement &parEle, Session &ses)
{
    QDomNamedNodeMap nmap;
    QString key, value;

    nmap = parEle.attributes();

    for (int i = 0; i < nmap.size(); i ++)
    {
        key = nmap.item(i).nodeName();
        value = nmap.item(i).nodeValue();

        ses.param[key] = value;
    }
}

bool ProjectFile::GetSessionList(SesList &sl)
{
    bool ret = false;
    QDomElement r;

    *root = doc->documentElement();

    QDomNodeList list;

    list = doc->elementsByTagName("type");
    for (int i = 0; i < list.size(); i ++)
    {
        QDomNode item = list.item(i);
        QDomElement type;
        Session ses;
        QDomNodeList seslist;

        type = item.toElement();
        seslist = type.elementsByTagName("session");

        ses.type = type.attribute("ID");

        for (int n = 0; n < seslist.size(); n ++)
        {
            QDomElement sesEle = seslist.item(n).toElement();

            ses.id = sesEle.attribute("ID");
            ses.name = sesEle.attribute("name");
            ses.show = sesEle.attribute("show");

            getSession(sesEle, ses);

            sl.append(ses);
            ret = true;
        }
    }

    return ret;
}

void ProjectFile::addType(QString &name)
{
    QDomElement type;

    type = doc->createElement("type");
    type.setAttribute("ID", name);
    root->appendChild(type);
}

void ProjectFile::AddSession(Session &ses)
{
    QDomNodeList list;
    int addtype = 0;

_again:
    list = doc->elementsByTagName("type");

    for (int i = 0; i < list.size(); i ++)
    {
        QDomNode item = list.item(i);
        QDomElement type;

        type = item.toElement();
        if (type.attribute("ID") == ses.type)
        {
            QDomElement e;

            e = doc->createElement("session");
            e.setAttribute("ID", ses.id);
            e.setAttribute("name", ses.name);
            e.setAttribute("show", ses.show);
            type.appendChild(e);

            addParam(e, ses);
            addtype = 1;
            break;
        }
    }

    if (addtype == 0)
    {
        addType(ses.type);
        goto _again;
    }
}

void ProjectFile::addParam(QDomElement &e, Session &ses)
{
    QDomElement child;
    QList<QString> keys;
    int cnt;

    keys = ses.param.keys();
    cnt = keys.size();

    child = doc->createElement("param");
    for (int i = 0; i < cnt; i ++)
    {
        QString key = keys[i];

        child.setAttribute(key, ses.param[key]);
    }
    e.appendChild(child);
}

void ProjectFile::init()
{
    QDomProcessingInstruction instruction;

    doc = new QDomDocument;
    root = new QDomElement;

    instruction = doc->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    *root = doc->createElement("Project");

    doc->appendChild(instruction);
    doc->appendChild(*root);

    prjfile = new QFile;
}

void ProjectFile::SetSesShow(QString &id, bool s)
{
   QString val;
   QDomNodeList list;

   val = s? "1":"0";

   list = doc->elementsByTagName("type");

   for (int i = 0; i < list.size(); i ++)
   {
       QDomNode item = list.item(i);
       QDomElement type, ele;

       type = item.toElement();
       ele = type.firstChildElement();

       while (!ele.isNull())
       {
           if (ele.attribute("ID") == id)
           {
               ele.setAttribute(QString("show"), val);
               Save();
               return;
           }

           ele = ele.nextSiblingElement();
       }
   }
}

void ProjectFile::DelSession(QString &id)
{
    QDomNodeList list;

    list = doc->elementsByTagName("type");

    for (int i = 0; i < list.size(); i ++)
    {
        QDomNode item = list.item(i);
        QDomElement type, ele;

        type = item.toElement();
        ele = type.firstChildElement();

        while (!ele.isNull())
        {
            if (ele.attribute("ID") == id)
            {
                type.removeChild(ele);
                Save();
                return;
            }

            ele = ele.nextSiblingElement();
        }
    }
}

void ProjectFile::Save()
{
    if (!prjfile->open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream out(prjfile);

    doc->save(out, 4);
    prjfile->close();
}
