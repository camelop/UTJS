#ifndef MYTICKETS_H
#define MYTICKETS_H

#include <QWidget>
#include <QDate>
#include "utjs_classes.hpp"
#include "communication.h"


namespace Ui {
    class MyTickets;
}

extern int communication_code;
extern sjtu::map<SeatType,QString> translate2;
extern QString _name,_id;

class MyTickets : public QWidget
{
    Q_OBJECT

public:
    explicit MyTickets(QWidget *parent = 0);
    QDate date;
    QString train_id,ticket_type,start_station,to_station;
    float price;
    sjtu::vector<Ticket> ticket_list;
    int ticket_cnt;
    Communication com;
    ~MyTickets();
private slots:
    void receiveshow(sjtu::vector<Ticket>);

    void on_RefundButton_clicked();

    void download_finished();

    void on_BackButton_clicked();

signals:
    void refund_f();

    void refund_t();

    void menu_user_show();
private:
    Ui::MyTickets *ui;
};
#endif // MYTICKETS_H
