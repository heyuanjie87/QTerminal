#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:
    void outData(const QByteArray &data);

private slots:
    void on_home_clicked();

    void on_start_clicked();

    void on_up_clicked();

    void on_down_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_reset_clicked();

    void on_color_clicked();

    void on_lend_clicked();

    void on_lstart_clicked();

    void on_lentire_clicked();

    void on_ldown_clicked();

    void on_lup_clicked();

    void on_screen_clicked();

    void on_crlf_clicked();

    void on_nl_clicked();

    void on_test1_clicked();

    void on_test2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
