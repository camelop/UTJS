#ifndef BUYTICKET_H
#define BUYTICKET_H

#include <QWidget>
#include <QDate>
#include "communication.h"

namespace Ui {
    class BuyTicket;
}

extern QString _id, _name;
extern int communication_code;
extern sjtu::map<SeatType,QString> translate2;

class BuyTicket : public QWidget
{
    Q_OBJECT

public:
    explicit BuyTicket(QWidget *parent = 0);
    QDate date;
    QString train_id, ticket_type,start_station,to_station;
    float price;
    int ticket_cnt;
    Train _Train;
    Communication com;
    ~BuyTicket();

private slots:
    void on_BackButton_clicked();

    void on_CancelButton_clicked();

    //void receiveshow(QDate,QString,QString,QString,float);

    void receiveshow(Train);

    void download_finished();
signals:
    void buy_t();

    void buy_f();

    void menu_user_show();
private:
    Ui::BuyTicket *ui;
};


#endif // BUYTICKET_H
