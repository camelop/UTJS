#ifndef MODIFYSELL_H
#define MODIFYSELL_H

#include <QWidget>
#include <QDate>
#include "communication.h"

namespace Ui {
    class ModifySell;
}

extern int communication_code;

class ModifySell : public QWidget
{
    Q_OBJECT

public:
    explicit ModifySell(QWidget *parent = 0);
    QString train_id;
    QDate date;
    Communication com;
    char ret[13];
    ~ModifySell();

private slots:
    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void on_CancelButton_clicked();

    void receiveshow();

    void download_finished();
signals:
    void menu_admin_show();
private:
    Ui::ModifySell *ui;
};

#endif // MODIFYSELL_H
