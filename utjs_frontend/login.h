#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include <QMouseEvent>
#include "communication.h"

namespace Ui {
class Login;
}

extern QString _id,_name;
extern int communication_code;

class Login : public QDialog
{
    Q_OBJECT

public:
    int flag=0;
    QString id,pswd;
    Communication com;
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private slots:
    void on_BackButton_clicked();

    void on_CancelButton_clicked();

    void on_RegisterButton_clicked();

    void receiveshow();

    void download_finished();

    void onTimeout();
signals:
    void menu_user_show();
    void menu_admin_show();
    void register_show();
    void log_f_show();
private:
    Ui::Login *ui;
    QMovie *movie;
    QPoint last;
    QTimer *timer;


};

#endif // LOGIN_H
