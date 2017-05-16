#ifndef MENU_USER_H
#define MENU_USER_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include "utjs_classes.hpp"
#include "communication.h"

namespace Ui {
    class Menu_User;
}

extern QString _id, _name;
extern int communication_code;

class Menu_User : public QWidget
{
    Q_OBJECT

public:
    explicit Menu_User(QWidget *parent = 0);
    Communication com;
    ~Menu_User();

private slots:
    void on_MyTicketsButton_clicked();

    void on_MoreTicketsButton_clicked();

    void on_MyInfoButton_clicked();

    void on_BackLogButton_clicked();

    void receiveshow();

    void download_finished();

signals:
    void back_log();

    //void ticketslist_show();

    void ticketslist_show(sjtu::vector<Ticket>);

    void saletickets_show();

    void modifypswd_show();

private:
    Ui::Menu_User *ui;
};

#endif // MENU_USER_H
