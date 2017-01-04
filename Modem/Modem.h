#ifndef MODEM_H
#define MODEM_H

#include <QDialog>

namespace Ui {
class Modem;
}

class Ymodem;

class Modem : public QDialog
{
    Q_OBJECT

public:
    explicit Modem(QWidget *parent = 0);
    ~Modem();

    void setFile(QString &name);
    void getFile(QString &name);
    void startTransfer(char type = 'C');
    void showStatus(const char *s);

public Q_SLOTS:
    void putData(const QByteArray &data);

private Q_SLOTS:
    void showTransfer(int total, int remain, float speed);
    void closed();

Q_SIGNALS:
    void outData(const QByteArray &data);
    void exitTransfer();

private:
    Ui::Modem *ui;
    Ymodem *ym;
    QString filename;
};

#endif // MODEM_H
