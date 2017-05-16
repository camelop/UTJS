#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "communication.h"

namespace Ui {
    class Register;
}

extern QString _id,_name;
extern int communication_code;

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    QString id,name,newpswd,repswd;
    Communication com;
    ~Register();

private slots:
    void on_BackButton_clicked();

    void on_BackLogButton_clicked();

    void receiveshow();

    void download_finished();
signals:
    void back_log();

    void menu_user_show();

    void regi_f();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
