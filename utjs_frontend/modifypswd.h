#ifndef MODIFYPSWD_H
#define MODIFYPSWD_H

#include <QWidget>
#include "communication.h"

namespace Ui {
    class ModifyPswd;
}

extern QString _id,_name;
extern int communication_code;

class ModifyPswd : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyPswd(QWidget *parent = 0);
    QString oldpswd,newpswd,repswd;
    Communication com;
    ~ModifyPswd();

private slots:
    void on_BackButton_clicked();

    void on_CancelButton_clicked();

    void receiveshow();

    void download_finished();
signals:
    void menu_user_show();
private:
    Ui::ModifyPswd *ui;
};

#endif // MODIFYPSWD_H
