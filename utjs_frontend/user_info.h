#ifndef USER_INFO_H
#define USER_INFO_H

#include <QWidget>
#include <QDate>
#include "utjs_classes.hpp"
#include "communication.h"

namespace Ui {
class User_Info;
}

extern int communication_code;
extern sjtu::map<SeatType,QString> translate2;
extern QString _id,_name;

class User_Info : public QWidget
{
    Q_OBJECT

public:
    explicit User_Info(QWidget *parent = 0);
    QDate date;
        QString train_id,ticket_type,start_station,to_station;
        float price;
        sjtu::vector<Ticket> ticket_list;
        int ticket_cnt;
        Communication com;
    ~User_Info();

private slots:
    void on_BackButton_clicked();

    void receiveshow(sjtu::vector<Ticket>);

signals:
    void menu_admin_show();
private:
    Ui::User_Info *ui;
};

#endif // USER_INFO_H
